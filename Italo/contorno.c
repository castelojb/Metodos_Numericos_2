#include <stdio.h>
#include <stdlib.h>
#include <vips/vips.h>

void detectar_arestas(VipsImage* origem, VipsImage** destino, unsigned char limite){
	int i, j, derivada;
	*destino = vips_image_new_from_image1(origem, 0);
	vips_image_inplace(origem);
	vips_image_inplace(*destino);

	for (j = 0; j < vips_image_get_height(origem); j++) {
		for (i = 0; i < vips_image_get_width(origem); i++) {
			if (i==0) {
				derivada = 2*abs(*VIPS_IMAGE_ADDR(origem,i+1,j) - *VIPS_IMAGE_ADDR(origem,i,j));
				*VIPS_IMAGE_ADDR((*destino),i,j) = ( derivada > 255 ) ? derivada = 255 : derivada;
			} else if (i==vips_image_get_width(origem)-1) {
				derivada = 2*abs(*VIPS_IMAGE_ADDR(origem,i,j) - *VIPS_IMAGE_ADDR(origem,i-1,j));
				*VIPS_IMAGE_ADDR((*destino),i,j) = ( derivada > 255 ) ? derivada = 255 : derivada;
			} else {
				*VIPS_IMAGE_ADDR((*destino),i,j) = derivada = abs(*VIPS_IMAGE_ADDR(origem,i+1,j) \
																- *VIPS_IMAGE_ADDR(origem,i-1,j));
			}
			if(limite){
				if (derivada > limite ) {
					*VIPS_IMAGE_ADDR((*destino),i,j) = 255;
				} else {
					*VIPS_IMAGE_ADDR((*destino),i,j) = 0;
				}
				
			}
		}
	}
}

int main(int argc, char *argv[]){
	VipsImage *imagem, *contornos;
	unsigned char limite = 0;
    if (argc>2) {
    	limite = atoi(argv[2]);
    }	

	if (VIPS_INIT( argv[0] )) {
		vips_error_exit(NULL);
	}

	imagem = vips_image_new_from_file(argv[1], NULL);
	vips_colourspace(imagem, &imagem, VIPS_INTERPRETATION_B_W, NULL);

	detectar_arestas(imagem, &contornos, limite);


	vips_image_write_to_file(contornos, "saida.png", NULL);
	g_object_unref(imagem);
	g_object_unref(contornos);

	vips_shutdown();
	return 0;
	}
