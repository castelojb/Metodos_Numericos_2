#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "CImg.h"

using namespace cimg_library;
using namespace std;


void drawScene(void);
void setup(void);
void resize(int w, int h);
void mouse(int button, int state, int x, int y);

float *reproducao, potencia;
int width, height, quant;

float derivada(float ant, float prox);

int main(int argc, char **argv){
	CImg<unsigned char> imagem(argv[1]);
	reproducao = new float[imagem.size()];
	float deri;
	
	width = imagem.width();
	height = imagem.height();
	quant = imagem.size();
	potencia = 5;
	
	for(int i = 0; i < width-1; i++){
		for(int j = 1; j < height-1; j++){
			reproducao[(i * height) + j] = derivada(imagem(i, j - 1), imagem(i, j + 1));
		}
	}
	
	for(int i = 1; i < width-1; i++){
		for(int j = 0; j < height-1; j++){
			reproducao[(i * height) + j] += derivada(imagem(i - 1, j), imagem(i + 1, j));
		}
	}
	
	glutInit(&argc, argv);

	//glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("teste");
	
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

void drawScene(void){
	int linha = 0;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_POINTS);
		for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				if(j != 0 && j < height-1 && reproducao[(i * height) + j] > potencia)
					glColor3f(0.0, 0.0, 0.0);
				else
					glColor3f(1.0, 1.0, 1.0);
				glVertex3f(i, height - j, 0.0);
			}
		}
	glEnd();

	glFlush();
}

void setup(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h){
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
	if(button == 3 && state == GLUT_DOWN && potencia){
		potencia--;
	}
	if(button == 4 && state == GLUT_DOWN){
		potencia++;
	}
	glutPostRedisplay();
}

float derivada(float ant, float prox){
	return abs((prox - ant));
}
