/*
PRA RODAR:
-------modo 1
g++ Luz.cpp Material.cpp Objeto.cpp Cone.cpp Esfera.cpp snowPOO.cpp -o main -lGL -lGLU -lGLEW -lglut -lm -Wno-write-strings


-------modo 2
g++ -c Funcoes.cpp -o Funcoes.o && g++ -c Luz.cpp -o Luz.o && g++ -c Objeto.cpp -o Objeto && g++ -c Material.cpp -o Material.o && g++ -c Cone.cpp -o Cone.o &&  g++ -c Esfera.cpp -o Esfera.o && g++ -c snowPOO.cpp -o snowPOO.o

g++ -o main Cone.o Esfera.o Objeto.o Material.o Luz.o Funcoes.o snowPOO.o -lGL -lGLU -lGLEW -lglut -lm -Wno-write-strings

--------modo 3
g++ -c *.cpp && g++ -o main *.o -O2 -L -lm -lpthread -lX11 -lGL -lGLU -lGLEW -lglut -Wno-write-strings && ./main


fazer camera e cenario
*/

#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>

#include <GL/freeglut.h>

#include "../lib/CImg/CImg.h"
#include "../header/ExibeMenu.h"

using namespace std;

static unsigned int   W_Npixels = 500, H_Npixels = 500;

char planoFundo[10][30];
int indiceFundo = 4;
int controlador = 4;
float precisao = 10;
double d;

void imagem_original(void);
void imagem_contornada(void);

void setCenario(){

//--------------------------IMAGEM FUNDO---------------------------//

	strcpy(planoFundo[0], "imagem/imagem1.jpg");
	strcpy(planoFundo[1], "imagem/imagem2.jpg");
	strcpy(planoFundo[2], "imagem/imagem3.jpg");
	strcpy(planoFundo[3], "imagem/imagem4.jpg");
	strcpy(planoFundo[4], "imagem/imagem5.jpg");
	strcpy(planoFundo[5], "imagem/imagem6.jpg");
	strcpy(planoFundo[6], "imagem/imagem7.jpg");
	strcpy(planoFundo[7], "imagem/imagem8.jpg");
	strcpy(planoFundo[8], "imagem/imagem9.jpg");

}

///////////////////FUNÇÃO QUE PINTA A TELA

void imagem_contornada(void) {
	using namespace cimg_library;
	
	CImg<unsigned char> plano(planoFundo[indiceFundo]);

	int x = 0, y = 0;
	double red = 0, green = 0, blue = 0;
	double red_original, green_original, blue_original, xRed, xGreen, xBlue, yRed, yGreen, yBlue;
	bool x_borda, y_borda;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

		for(y = 1; y < H_Npixels; y++){

			for(x = 1; x < W_Npixels; x++){

				red_original = (double)plano(x, y, 0)/255;
				green_original = (double)plano(x, y, 1)/255;
				blue_original = (double)plano(x, y, 2)/255;

				glColor3f(red_original, green_original, blue_original);
				glVertex2f(x-1, y-1);

			}

			for (int xaux = W_Npixels; xaux < 2*W_Npixels; xaux++) {
				x = xaux - W_Npixels + 1;
				xRed = abs(plano(x+1, y, 0) - plano(x-1, y, 0));
				xGreen = abs(plano(x+1, y, 1) - plano(x-1, y, 1));
				xBlue = abs(plano(x+1, y, 2) - plano(x-1, y, 2));

				yRed = abs(plano(x, y+1, 0) - plano(x, y-1, 0));
				yGreen = abs(plano(x, y+1, 1) - plano(x, y-1, 1));
				yBlue = abs(plano(x, y+1, 2) - plano(x, y-1, 2));

				x_borda = xRed > precisao or xGreen > precisao or xBlue > precisao;
				y_borda = yRed > precisao or yGreen > precisao or yBlue > precisao;

				if (x_borda or y_borda) {
					red = 1;
					green = 1;
					blue = 1;

				} else {
					red = 0;
					green = 0;
					blue = 0;	
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
	setCenario();

	d = 700;

}

//Pra fechar a janeça com o ESC
void Teclado(unsigned char key, int x, int y) {	
	switch((char)key) {
		case 27: //ESC
			limpaMenu(); glutDestroyWindow(0); exit(0); break;

		case '1': 
			indiceFundo = 0; break;
		
		case '2': 
			indiceFundo = 1; break;

		case '3': 
			indiceFundo = 2; break;
		
		case '4': 
			indiceFundo = 3; break;
		
		case '5': 
			indiceFundo = 4; break;
		
		case '6': 
			indiceFundo = 5; break;

		case '7': 
			indiceFundo = 6; break;

		case '8': 
			indiceFundo = 7; break;

		case '+': 
			precisao += 0.5; break;

		case '-': 
			if (precisao - 0.5 <= 0) precisao = 0.5;
			else precisao -= 0.5; break;

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
	glutDisplayFunc(imagem_contornada);
	glutReshapeFunc(redimenciona);
	glutKeyboardFunc(Teclado);
	glutCloseFunc(limpaMenu);


	glutMainLoop(); 
}
