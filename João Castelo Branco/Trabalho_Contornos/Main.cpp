/*
 * Main.cpp
 *
 *  Created on: 21 de set de 2018
 *      Author: joao
 */

//includes do c++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

//include da imagem
#include "CImg.h"

//includes do GL
#include <GL/glew.h>
#include <GL/glut.h>
# include <GL/freeglut.h>

using namespace std;

//nome da foto
string nome="BH-noite.jpg";

bool color = false;

using namespace cimg_library;
CImg<unsigned char> fundo(nome.data());


//as dimensoes se adaptam com a imagem agora
GLdouble windowWidth  = fundo.width();
GLdouble windowHeight = fundo.height();

int window;

//CImg fundo;

GLuint* vao;
GLuint* vbo;
GLuint* ibo;

//inicializando a classe cimg


//fazendo as derivadas com filosofias
double Derivada_Forward(int x , int y){
	
	double valor_da_cor_na_posicao =(double)fundo(x, windowHeight-y, 0, 0)/255;
	double valor_da_cor_na_posicao_posterior = (double)fundo(x+1, windowHeight-y, 0, 0)/255;

	return ( valor_da_cor_na_posicao_posterior - valor_da_cor_na_posicao );
}

double Derivada_Backward(int x , int y){
	
	double valor_da_cor_na_posicao =(double)fundo(x, windowHeight-y, 0, 0)/255;

	double valor_da_cor_na_posicao_anterior = (double)fundo(x-1, windowHeight-y, 0, 0)/255;

	return ( valor_da_cor_na_posicao - valor_da_cor_na_posicao_anterior );
}

double Derivada_Central(int x , int y){
	
	double valor_da_cor_na_posicao_posterior =(double)fundo(x+1, windowHeight-y, 0, 0)/255;
	double valor_da_cor_na_posicao_anterior = (double)fundo(x-1, windowHeight-y, 0, 0)/255;

	return ( valor_da_cor_na_posicao_posterior - valor_da_cor_na_posicao_anterior )/2;
}

//verificadores de posicao para o eixo X
bool isFirstPixel_X(int x){
	if(x==0){
		return true;
	}else{
		return false;
	}
}

bool isLastPixel_X(int x){
	
	if(x==windowWidth){
		return true;
	}else{
		return false;
	}	
}

bool isCentralPixel_X(int x){
	if(not isFirstPixel_X(x) and not isLastPixel_X(x)){
		return true;
	}else{
		return false;
	}
}

//funcao para calcular a fronteira
void setFronteira (int x, int y , vector<int> &X_contorno , vector<int> &Y_contorno, double dead_line){
	
	double derivada;
	
	if(isFirstPixel_X(x)){
		derivada=Derivada_Forward(x,y);
	}
	
	
	if(isCentralPixel_X(x)){
		derivada = Derivada_Central(x,y);
	}

	
	if(isLastPixel_X(x)){
	
		derivada = Derivada_Backward(x,y);
	}
	
	//inclinacao da reta foi maior que a dead line, ela deve ser um contorno
	if(derivada >=dead_line){
		X_contorno.push_back(x);
		Y_contorno.push_back(y);
	}

}


void Desenho(void){

	cout<<"Fazendo imagem"<<endl;
	

	//limpando a tela
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
	//vector's que irao armazenar os x e y em que foram detectados contornos
	vector<int> X_contorno;
	vector<int> Y_contorno;



	//pintando o fundo sem contorno
	for(int j = 0; j < windowHeight; ++j){
		for(int i = 0; i < windowWidth; ++i){
			
			//x e y
			double x = (i  - windowWidth/2);
			double y = (j - windowHeight/2);

			double Ipix;
			
			Ipix = (double)fundo(i, windowHeight-j, 0, 0)/255;

			//Ipix[0] = (double)fundo(i, windowHeight-j, 0, 0)/255;
			//Ipix[1] = (double)fundo(i, windowHeight-j, 0, 1)/255;
			//Ipix[2] = (double)fundo(i, windowHeight-j, 0, 2)/255;
			
			if(color){
				//com cor
				glColor3f(Ipix, Ipix, Ipix);	
			}else{
				//fundo branco
				glColor3f(1,1,1);	
			}

			
			//opcao de pintar com o fundo branco
			//glColor3f(1,1,1);
			
			glVertex2f(x, y);
			
			//verificando fronteira e setando a dead line
			setFronteira(i, j , X_contorno , Y_contorno , 0.02);

		}
	}

	//pintando o contorno
	for(int i=0 ; i<X_contorno.size() ; i++){
		
		//cor do contorno
		glColor3f( 0 , 0, 0);
		
		//posicao do pixel do contorno
		double x = (X_contorno[i]  - windowWidth/2);
		double y = (Y_contorno[i] - windowHeight/2);

		glVertex2f(x , y);
	}


		
	glEnd();
	glFlush();
}


// Callback do GLUT: Chamado na criação da janela e toda vez que ela for redimensionada
void _Redimensionar(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	// Redefinição do viewport e projeção
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2, w/2, -h/2, h/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

//chaves do teclado
void _Teclado(unsigned char key, int x, int y)
{
	switch((char)key)
	{
		// ESC
		case 27:
			glutDestroyWindow(window);
			exit(0);
			break;

		//muda a foto
		case 'w':
			fundo.load("marie.png");
			windowWidth  = fundo.width();
			windowHeight = fundo.height();
			
			break;

		case 's':
			fundo.load("BH-noite.jpg");
			windowWidth  = fundo.width();
			windowHeight = fundo.height();
			
			break;

		case 'a':
			fundo.load("Mulher.jpg");
			windowWidth  = fundo.width();
			windowHeight = fundo.height();
			
			break;
		//muda o fundo
		case 'c':
			color = not color;
			break;

	}

	glutPostRedisplay();
}

int main(int argc, char *argv[]){
	

	
	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow(nome.data());

	glewExperimental = GL_TRUE;

	//Definição de callbacks
	glutKeyboardFunc(_Teclado);
	glutReshapeFunc(_Redimensionar);
	glutDisplayFunc(Desenho);

	glutMainLoop();
	exit(0);

	
	return 0;
}
