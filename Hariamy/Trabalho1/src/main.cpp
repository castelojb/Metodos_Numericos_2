
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>

#include <GL/freeglut.h>

#include "../lib/CImg/CImg.h"
#include "../header/ExibeMenu.h"

using namespace std;

static unsigned int   W_Npixels = 500, H_Npixels = 600;

unsigned const int tamanho_vetor_imagens = 16;
char vetor_imagens[tamanho_vetor_imagens][30];
int indice_imagens = 4;
int controlador = 4;
float precisao = 30;
double d;
bool colorido = false;


void contorno(void) {
	using namespace cimg_library;
	
	CImg<unsigned char> imagem(vetor_imagens[indice_imagens]);

	int x = 0, y = 0;
	double red = 0, green = 0, blue = 0;
	double xRed, xGreen, xBlue, yRed, yGreen, yBlue;
	bool x_borda, y_borda;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

		for(y = 1; y < H_Npixels+1; y++){

			for(x = 1; x < W_Npixels; x++){

				red   = (double)imagem(x, y, 0)/255;
				green = (double)imagem(x, y, 1)/255;
				blue  = (double)imagem(x, y, 2)/255;

				glColor3f(red, green, blue);
				glVertex2f(x-1, y-1);

			}

			for (int xaux = W_Npixels; xaux < 2*W_Npixels; xaux++) {
				x = xaux - W_Npixels + 1;

				xRed   = abs( imagem(x+1, y, 0) - imagem(x-1, y, 0) );
				xGreen = abs( imagem(x+1, y, 1) - imagem(x-1, y, 1) );
				xBlue  = abs( imagem(x+1, y, 2) - imagem(x-1, y, 2) );

				yRed   = abs( imagem(x, y+1, 0) - imagem(x, y-1, 0) );
				yGreen = abs( imagem(x, y+1, 1) - imagem(x, y-1, 1) );
				yBlue  = abs( imagem(x, y+1, 2) - imagem(x, y-1, 2) );
				
			

				x_borda = xRed > precisao or xGreen > precisao or xBlue > precisao;
				y_borda = yRed > precisao or yGreen > precisao or yBlue > precisao;

				if (x_borda or y_borda) {
					red = 0;
					green = 0;
					blue = 0;

				} else if (colorido){
					red = (double)imagem(x, y, 0)/255;
					green = (double)imagem(x, y, 1)/255;
					blue = (double)imagem(x, y, 2)/255;	
				
				} else {
					red = 1;
					green = 1;
					blue = 1;
				}

				glColor3f(red, green, blue);
				glVertex2f(xaux, y-1);
			}
		}
	
	glEnd();
	glFlush();

}


void setGlobais(){
	glClearColor(0.8, 0.9, 0.9, 0.0);

	strcpy(vetor_imagens[0], "imagem/imagem0.jpg");
	strcpy(vetor_imagens[1], "imagem/imagem1.jpg");
	strcpy(vetor_imagens[2], "imagem/imagem2.jpg");
	strcpy(vetor_imagens[3], "imagem/imagem3.jpg");
	strcpy(vetor_imagens[4], "imagem/imagem4.jpg");
	strcpy(vetor_imagens[5], "imagem/imagem5.jpg");
	strcpy(vetor_imagens[6], "imagem/imagem6.jpg");
	strcpy(vetor_imagens[7], "imagem/imagem7.jpg");
	strcpy(vetor_imagens[8], "imagem/imagem8.jpg");
	strcpy(vetor_imagens[9], "imagem/imagem9.jpg");
	strcpy(vetor_imagens[10], "imagem/imagem10.jpg");
	strcpy(vetor_imagens[11], "imagem/imagem11.jpg");
	strcpy(vetor_imagens[12], "imagem/imagem12.jpg");
	strcpy(vetor_imagens[13], "imagem/imagem13.jpg");
	strcpy(vetor_imagens[14], "imagem/imagem14.jpg");
	strcpy(vetor_imagens[15], "imagem/imagem15.jpg");

}

//Pra fechar a janeça com o ESC
void Teclado(unsigned char key, int x, int y) {	
	switch((char)key) {
		case 27: //ESC
			limpaMenu(); glutDestroyWindow(0); exit(0); break;

		case 'a':
			if (indice_imagens + 1 == tamanho_vetor_imagens) indice_imagens = 0;
			else indice_imagens ++; break;

		case 'A':
			if (indice_imagens + 1 == tamanho_vetor_imagens) indice_imagens = 0;
			else indice_imagens ++; break;

		case 'd':
			if (indice_imagens - 1 == -1) indice_imagens = tamanho_vetor_imagens - 1;
			else indice_imagens --; break;

		case 'D':
			if (indice_imagens - 1 == -1) indice_imagens = tamanho_vetor_imagens - 1;
			else indice_imagens --; break;

		case 32: //Espaço
			if (indice_imagens - 1 == -1) indice_imagens = tamanho_vetor_imagens - 1;
			else indice_imagens --; break;

		case '+': 
			precisao += 0.5; break;

		case '-': 
			if (precisao - 0.5 <= 0) precisao = 0.5;
			else precisao -= 0.5; break;

		case 'c':
			if (colorido) colorido = false;
			else colorido = true; break;

		case 'C':
			if (colorido) colorido = false;
			else colorido = true; break;

		default:
			break;
	}
	glutPostRedisplay();
}

void redimenciona(int w, int h) {
	glViewport(0, 0,  w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 2*W_Npixels, H_Npixels, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv) {
	exibeMenu();
	setGlobais();

	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
	glutInitWindowSize(2*W_Npixels, H_Npixels);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("    ORIGINAL  X  CONTORNO ");
	glutDisplayFunc(contorno);
	glutReshapeFunc(redimenciona);
	glutKeyboardFunc(Teclado);
	glutCloseFunc(limpaMenu);


	glutMainLoop(); 
}
