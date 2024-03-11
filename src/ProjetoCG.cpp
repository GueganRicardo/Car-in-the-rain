#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "RgbImage.h"

#define PI		 3.14159

GLint wScreen = 800, hScreen = 600;
GLfloat tam = 0.5;
GLint   msec = 30;
GLint   raio_carro = 4;
GLint   angulo_rodar = 1;
GLint   angulo_inc = 1;
GLfloat	limpa_vidros = 0.1;
GLfloat	limpa_vidros_inc = 0.02;
GLfloat chuva_x[1024];
GLfloat chuva_y[1024];
GLfloat chuva_z[1024];
GLint tipo_mat = 1;
GLint polig = 1;
GLint transp = 1;
GLint intensidade = 1;
GLint cor = 1;
RgbImage imag;
GLuint   texture[3];

//Malha
GLint quads = 100;
//Materias
GLfloat material_vermelhometal_ambient[] = { 0.5, 0.0, 0.0, 1 };
GLfloat material_vermelhometal_diffuse[] = { 1.0, 0.0, 0.0, 1 };
GLfloat material_vermelhometal_specular[] = {1, 1.0, 1.0, 1 };
GLfloat material_vermelhometal_shininess = 15.0;

GLfloat material_azulmetal_ambient[] = { 0, 0, 0.5, 1 };
GLfloat material_azulmetal_diffuse[] = { 0, 0, 1.0, 1 };
GLfloat material_azulmetal_specular[] = { 1, 1.0, 1.0, 1 };
GLfloat material_azulmetal_shininess = 15.0;

GLfloat material_agua_ambient[] = { 0.0, 0.5, 1.0, 1 };
GLfloat material_agua_diffuse[] = { 0.0, 0.5, 1.0, 0.4};
GLfloat material_agua_specular[] = { 1.0, 1.0, 1.0,1 };
GLfloat material_agua_shininess = 50.0;

GLfloat material_vidros_ambient[] = { 0.0, 0.5, 1.0, 1 };
GLfloat material_vidros_diffuse[] = { 0.0, 0.5, 1.0, 0.5 };
GLfloat material_vidros_specular[] = { 1.0, 1.0, 1.0,1 };
GLfloat material_vidros_shininess = 50.0;

GLfloat material_rodas_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat material_rodas_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat material_rodas_specular[] = { 1.0, 1.0, 1.0,1 };
GLfloat material_rodas_shininess = 50.0;

GLfloat material_verduras_ambient[] = { 0.0, 0.5, 0.0, 1.0 };
GLfloat material_verduras_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat material_verduras_specular[] = { 1.0, 1.0, 1.0,1 };
GLfloat material_verduras_shininess = 50.0;

GLfloat material_tronco_ambient[] = { 0.5, 0.25, 0.0, 1.0 };
GLfloat material_tronco_diffuse[] = { 0.5, 0.25, 0.0, 1.0 };
GLfloat material_tronco_specular[] = { 1.0, 1.0, 1.0,1 };
GLfloat material_tronco_shininess = 50.0;

GLfloat material_farois_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat material_farois_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat material_farois_specular[] = { 1.0, 1.0, 1.0,1 };
GLfloat material_farois_shininess = 50.0;
//Fim Materias----------------

//Luz
GLfloat luzGlobal[4] = { 0.1,0.1,0.1,1.0 };

//Luz da lua
GLfloat posLuz1[4] = { 0,0.5,1,0}; 
GLfloat corAmbLuz1[4] = { 0.2, 0.2, 0.3, 1.0 };
GLfloat corDifLuz1[4] = { 0.1, 0.3, 0.3, 1.0 };
GLfloat corEspecLuz1[4] = { 0.2, 0.2, 0.2, 1.0 };

GLfloat corVermAmbLuz1[4] = { 0.3, 0.1, 0.1, 1.0 };
GLfloat corVermDifLuz1[4] = { 0.3, 0.1, 0.1, 1.0 };

GLfloat corDiaAmbLuz1[4] = { 0.2, 0.2, 0.3, 1.0 };
GLfloat corDiaDifLuz1[4] = { 0.1, 0.3, 0.3, 1.0 };

//Farois do carro
GLfloat posLuz2[4] = { 0,1,0,1 };
GLfloat diracaoLuz2[3] = { 1, 0, 0};
GLfloat corAmbLuz2[4] = { 1,1,1,1 };
GLfloat corDifLuz2[4] = { 1,1,1,1 };
GLfloat corEspecLuz2[4] = { 1,1,1,1 };
GLfloat farol_exponent[1] = { 2.0 };
GLfloat farol_angulo[1] = { 30.0 };
GLfloat atenuacaoCLuz2[1] = { 1.0 };
GLfloat atenuacaoLLuz2[1] = {0.25};
GLfloat atenuacaoQLuz2[1] = { 0.1};

//Fim Luz----------------
static GLfloat posicoes[] = {
	//・・・・・・・・・・・・・・・・・・・ x=tam (Esquerda)
			-tam,  -tam,  tam,	// 0 
			-tam,   tam,  tam,	// 1 
			-tam,   tam, -tam,	// 2 
			-tam,  -tam, -tam,	// 3 
			//・・・・・・・・・・ Direita
			tam,  -tam,  tam,	// 4 
			tam,   tam,  tam,	// 5 
			tam,   tam, -tam,	// 6 
			tam,  -tam, -tam,	// 7 
			//・・・・・・・・・・・(tampo 1)
			-tam,  2.75 * tam,  -tam,	// 8 
			-tam,  2.75 * tam, tam,	// 9 
			tam,  2.75 * tam, tam,	// 10 
			tam,  2.75 * tam, -tam,	// 11 
			//. . . . . . . . . .(tampo 2)
			-tam, 2 * tam,  -tam,
			-tam, 2 * tam, tam,
			2 * tam,  2 * tam, tam,
			2 * tam,  2 * tam, -tam,
			//chao
			-100,0,-100,
			-100,0,100,
			100,0,100,
			100,0,-100,
			//frente1
			tam, 2.75 * tam, tam,
			tam, 2 * tam, tam,
			tam, 2 * tam, -tam,
			tam, 2.75 * tam, -tam,
			//frente2
			2 * tam, 2 * tam, tam,
			2 * tam,  tam, tam,
			2 * tam,  tam, -tam,
			2 * tam, 2 * tam, -tam,
			//FarolE
			2.01 * tam, 1.95 * tam, 0.95 * tam,
			2.01 * tam,  1.80 * tam, 0.95 * tam,
			2.01 * tam,  1.80 * tam, 0.75 * tam,
			2.01 * tam, 1.95 * tam, 0.75 * tam,
			//FarolD
			2.01 * tam, 1.95 * tam, 0.75 * -tam,
			2.01 * tam,  1.80 * tam, 0.75 * -tam,
			2.01 * tam,  1.80 * tam, 0.95 * -tam,
			2.01 * tam, 1.95 * tam, 0.95 * -tam,
			//vidrofrente
			1.01 * tam, 2.68 * tam, 0.9 * tam,
			1.01 * tam, 2.10 * tam, 0.9 * tam,
			1.01 * tam, 2.10 * tam,  0.9 * -tam,
			1.01 * tam, 2.68 * tam,  0.9 * -tam,
			//baixo
			-tam,  tam,  -tam,
			-tam,  tam, tam,
			2 * tam,   tam, tam,
			2 * tam,   tam, -tam,
			//LadoDirRet
			-tam,2.75 * tam,tam,
			-tam,tam,tam,
			tam,tam,tam,
			tam,2.75 * tam,tam,
			//LadoDirRetmini
			tam,2 * tam,tam,
			tam,tam,tam,
			2 * tam,tam,tam,
			2 * tam,2 * tam,tam,
			//LadoDirJanelaTrás
			-tam * 0.95,2.70 * tam,tam * 1.01,
			-tam * 0.95,2.05 * tam,tam * 1.01,
			-tam * 0.05,2.05 * tam,tam * 1.01,
			-tam * 0.05,2.70 * tam,tam * 1.01,
			//LadoDirJanelaFrente
			0.05 * tam,2.70 * tam,tam * 1.01,
			0.05 * tam,2.05 * tam,tam * 1.01,
			0.95 * tam,2.05 * tam,tam * 1.01,
			0.95 * tam,2.70 * tam,tam * 1.01,
			//Traseira
			-tam,tam * 2.75,-tam,
			-tam,tam,-tam,
			-tam,tam, tam,
			-tam,tam * 2.75,tam,
			//escape
			-tam * 1.01,tam * 1.2,tam * 0.7,
			-tam * 1.01,tam * 1.05,tam * 0.7,
			-tam * 1.01,tam * 1.05, tam * 0.95,
			-tam * 1.01,tam * 1.2,tam * 0.95,
			//LadoEsqGrande
			tam,2.75 * tam,-tam,
			tam,tam,-tam,
			-tam,tam,-tam,
			-tam,2.75 * tam,-tam,
			//LadoEsqPequeno
			2 * tam,2 * tam,-tam,
			2 * tam,tam,-tam,
			tam,tam,-tam,
			tam,2 * tam,-tam,
			//LadoEsqJanelaTrás
			-tam * 0.05,2.70 * tam,-tam * 1.01,
			-tam * 0.05,2.05 * tam,-tam * 1.01,
			-tam * 0.95,2.05 * tam,-tam * 1.01,
			-tam * 0.95,2.70 * tam,-tam * 1.01,
			//LadoEsqJanelaFrente
			0.95 * tam, 2.70 * tam, -tam * 1.01,
			0.95 * tam, 2.05 * tam, -tam * 1.01,
			0.05 * tam, 2.05 * tam, -tam * 1.01,
			0.05 * tam, 2.70 * tam,-tam * 1.01,
			//Rodaext
			0, tam * 0.6, 0,
			tam * 0.4, tam * 0.4, 0,
			tam * 0.6, 0, 0,
			tam * 0.4, -tam * 0.4, 0,
			0, -tam * 0.6, 0,
			-tam * 0.4, -tam * 0.4, 0,
			-tam * 0.6, 0, 0,
			-tam * 0.4, tam * 0.4, 0,
			//ArvoreFrente
			2 * tam,6 * tam,2 * tam,
			2 * tam,0,2 * tam,
			2 * tam,0,-2 * tam,
			2 * tam,6 * tam,-2 * tam,
			//Arvoreesq
			-2 * tam, 6 * tam, 2 * tam,
			-2 * tam, 0, 2 * tam,
			2 * tam, 0, 2 * tam,
			2 * tam, 6 * tam, 2 * tam,
			//Arvoredir
			2 * tam, 6 * tam, -2 * tam,
			2 * tam, 0, -2 * tam,
			-2 * tam, 0, -2 * tam,
			-2 * tam, 6 * tam, -2 * tam,
			//ArvoreTras
			-2 * tam, 6 * tam, -2 * tam,
			-2 * tam, 0, -2 * tam,
			-2 * tam, 0, 2 * tam,
			-2 * tam, 6 * tam, 2 * tam,
			//Folhagem
			4 * tam, 6 * tam, 4 * tam,
			4 * tam, 6 * tam, -4 * tam,
			-4 * tam, 6 * tam, -4 * tam,
			-4 * tam, 6 * tam, 4 * tam,
			//FolhagemFrente
			4 * tam, 10 * tam, 4 * tam,
			4 * tam, 6 * tam, 4 * tam,
			4 * tam, 6 * tam, -4 * tam,
			4 * tam, 10 * tam, -4 * tam,
			//Folhagemesq
			-4 * tam, 10 * tam, 4 * tam,
			-4 * tam, 6 * tam, 4 * tam,
			4 * tam, 6 * tam, 4 * tam,
			4 * tam, 10 * tam, 4 * tam,
			//Folhagemdir
			4 * tam, 10 * tam, -4 * tam,
			4 * tam, 6 * tam, -4 * tam,
			-4 * tam, 6 * tam, -4 * tam,
			-4 * tam, 10 * tam, -4 * tam,
			//FolhagemTras
			-4 * tam, 10 * tam, -4 * tam,
			-4 * tam, 6 * tam, -4 * tam,
			-4 * tam, 6 * tam, 4 * tam,
			-4 * tam, 10 * tam, 4 * tam,
			//chuva
			0, 0.05 * tam, 0.03 * tam,
			0, -0.05 * tam, 0.03 * tam,
			0, -0.05 * tam, -0.03 * tam,
			0, 0.05 * tam, -0.03 * tam,
			//parabrisas
			1.02 * tam, 2.65 * tam, 0.87 * tam,
			1.02 * tam, 2.13 * tam, 0.87 * tam,
			1.02 * tam, 2.13 * tam, 0.84 * tam,
			1.02 * tam, 2.65 * tam, 0.84 * tam,
};


static GLfloat normais[] = {
	//・・・・・・・・・・・・・・・・・・・ x=tam (Esquerda)
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		//・・・・・・・・・・・・・・・・・・・ x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//tampo 1
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		// tampo 2
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		//pavimento
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		//Frente1
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//Frente2
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//FarolE
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//FarolD
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//Vidro Frente
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//baixo
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//LadoDirRet
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//LadoDirRetmini
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//LadoDirJanelaFrente
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//LadoDirJanelaTrás
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//traseira
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		//escape
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		//LadoEsqGrande
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		//LadoEsqPequeno
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		//LadoEsqJanelaFrente
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		//LadoEsqJanelaTrás
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		//Roda
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//ArvoreFrente
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//Arvoreesq
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		//Arvoredir
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		//Arvoretras
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		//Folhagem
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		//FolhagemFrente
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//Folhagemeesq
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		//Folhagemdir
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		//Folhagemtras
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		//chuva
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//parabrisas
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
};

static GLfloat texturas[] = {
0,0,
0, 0,
0, 0,
0, 0,
//
0,0,
0, 0,
0, 0,
0, 0,
//
0,0,
0, 0,
0, 0,
0, 0,
//
0,0,
0, 0,
0, 0,
0, 0,
//
0,0,
0, 0,
0, 0,
0, 0,
//
0,0,
0, 0,
0, 0,
0, 0,
//frente2
0,0,
0, 0,
0, 0,
0, 0,
//FarolE
0,0,
0, 0,
0, 0,
0, 0,
//FarolD
0,0,
0, 0,
0, 0,
0, 0,
//vidrofrente
0,0,
0, 0,
0, 0,
0, 0,
//baixo
0,0,
0, 0,
0, 0,
0, 0,
//LadoDirRet
0, 0,
0, 0,
0, 0,
0, 0,
//LadoDirRetmini
0, 0,
0, 0,
0, 0,
0, 0,
//LadoDirJanelaTrás
0, 0,
0, 0,
0, 0,
0, 0,
//LadoDirJanelaFrente
0,0,
0, 0,
0, 0,
0, 0,
//Traseira
0, 0,
0, 0,
0, 0,
0, 0,
//escape
0,0,
0, 0,
0, 0,
0, 0,
//LadoEsqGrande
0,0,
0, 0,
0, 0,
0, 0,
//LadoEsqPequeno
0,0,
0, 0,
0, 0,
0, 0,
//LadoEsqJanelaTrás
0,0,
0, 0,
0, 0,
0, 0,
//LadoEsqJanelaFrente
0, 0,
0, 0,
0, 0,
0, 0,
//Rodaext
0, 0,
0, 0,
0, 0,
0, 0,
0, 0,
0, 0,
0, 0,
0, 0,
//ArvoreFrente
6,4,
0,4,
0,0,
6,0,
//Arvoreesq
6, 4,
0, 4,
0, 0,
6, 0,
//Arvoredir
6, 4,
0, 4,
0, 0,
6, 0,
//ArvoreTras
6, 4,
0, 4,
0, 0,
6, 0,
//Folhagem
0,0,
10,0,
10, 10,
0,10,
//FolhagemFrente
0, 2,
0, 0,
3, 0,
3, 2,
//Folhagemesq
0, 2,
0, 0,
3, 0,
3, 2,
//Folhagemdir
0, 2,
0, 0,
3, 0,
3, 2,
//FolhagemTras
0, 2,
0, 0,
3, 0,
3, 2,
//chuva
0, 0,
0, 0,
0, 0,
0, 0,
//parabrisas
0,0,
0, 0,
0, 0,
0, 0,
};

static GLuint     esquerda[] = { 0,1,2,3 };
static GLuint     direita[] = { 7,6,5,4 };
static GLuint     cima1[] = { 8, 9, 10,11 };
static GLuint     cima2[] = { 12, 13, 14,15 };
static GLuint     pavimento[] = { 16,17,18,19 };
static GLuint     frente1[] = { 20,21,22,23 };
static GLuint     frente2[] = { 24,25,26,27 };
static GLuint     farol1[] = { 28,29,30,31 };
static GLuint     farol2[] = { 32,33,34,35 };
static GLuint     Vidro_frente[] = { 36,37,38,39 };
static GLuint    Baixo[] = { 40,41,42,43 };
static GLuint    LadoDirRet[] = { 44,45,46,47 };
static GLuint    LadoDirRetMini[] = { 48,49,50,51 };
static GLuint    LadoDirJanelaFrente[] = { 52,53,54,55 };
static GLuint   LadoDirJanelaTrás[] = { 56,57,58,59 };
static GLuint    Traseira[] = { 60,61,62,63 };
static GLuint    CanoEscape[] = { 64,65,66,67 };
static GLuint    LadoEsqGrande[] = { 68,69,70,71 };
static GLuint    LadoEsqPequeno[] = { 72,73,74,75 };
static GLuint    LadoEsqJanelaTrás[] = { 76,77,78,79 };
static GLuint    LadoEsqJanelaFrente[] = { 80,81,82,83 };
static GLuint    Roda[] = { 84,85,86,87,88,89,90,91 };
static GLuint    Rodaint[] = { 91,90,89,88,87,86,85,84 };
static GLuint   parabrisas[] = { 132,133,134,135 };

void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, posLuz1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, corAmbLuz1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, corDifLuz1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, corEspecLuz1);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_POSITION, posLuz2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, corAmbLuz2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, corDifLuz2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, corEspecLuz2);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, farol_exponent);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, farol_angulo);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, diracaoLuz2);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, atenuacaoCLuz2);
	glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, atenuacaoLLuz2);
	glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, atenuacaoQLuz2);
	glEnable(GL_LIGHT1);
}

void desenhaCarro() {
	glPushMatrix();//tentar fazer tudo em uma só chamada
	if (tipo_mat) {
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_vermelhometal_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_vermelhometal_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_vermelhometal_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_vermelhometal_shininess);
	}
	else {
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_azulmetal_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_azulmetal_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_azulmetal_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_azulmetal_shininess);
	}
	glRotatef(angulo_rodar, 0, 1, 0);
	glTranslatef(0, 0, raio_carro);
	glBlendFunc(GL_ONE, GL_ZERO);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoDirRet);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoDirRetMini);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Traseira);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, CanoEscape);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoEsqGrande);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoEsqPequeno);
	//farois
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_farois_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_farois_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_farois_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_farois_shininess);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, farol2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, farol1);
	//vidros
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_vidros_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_vidros_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_vidros_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_vidros_shininess);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Vidro_frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoEsqJanelaFrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoEsqJanelaTrás);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoDirJanelaFrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, LadoDirJanelaTrás);
	//--------
	glBlendFunc(GL_ONE, GL_ZERO);
	glPushMatrix();
	glTranslatef(0, 0, -limpa_vidros);
	limpa_vidros += limpa_vidros_inc;
	if (-limpa_vidros < -0.9) {
		limpa_vidros_inc = -limpa_vidros_inc;
	}
	if (-limpa_vidros > -0.1) {
		limpa_vidros_inc = -limpa_vidros_inc;
	}
	//rodas
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_rodas_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_rodas_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_rodas_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_rodas_shininess);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, parabrisas);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(tam, tam, -tam * 1.01);
	glRotatef(-angulo_rodar * 2, 0, 0, 1);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Roda);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Rodaint);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(tam, tam, tam * 1.01);
	glRotatef(-angulo_rodar * 2, 0, 0, 1);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Roda);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Rodaint);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-tam * 0.5, tam, -tam * 1.01);
	glRotatef(-angulo_rodar * 2, 0, 0, 1);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Roda);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Rodaint);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-tam * 0.5, tam, tam * 1.01);
	glRotatef(-angulo_rodar * 2, 0, 0, 1);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Roda);
	glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, Rodaint);
	glPopMatrix();
	//----------
	glPopMatrix();

}

static GLuint   Arvfrente[] = { 92,93,94,95 };
static GLuint   Arvesq[] = { 96,97,98,99 };
static GLuint   Arvdir[] = { 100,101,102,103 };
static GLuint   Arvtras[] = { 104,105,106,107 };
static GLuint   FolhaBaixo[] = { 108,109,110,111 };
static GLuint   Folhafrente[] = { 112,113,114,115 };
static GLuint   Folhaesq[] = { 116,117,118,119 };
static GLuint   Folhadir[] = { 120,121,122,123 };
static GLuint   Folhatras[] = { 124,125,126,127 };
static GLuint   Chuva[] = { 128,129,130,131 };
static GLuint   Chuva_inv[] = { 131,130,129,128 };

void desenha_chao() {
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	float lado=200.0/quads;
	glPushMatrix();
	glTranslatef(-100, 0, -100);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (int i = 0; i < quads; i++) {
		for (int f = 0; f < quads; f++) {
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(i*lado,0.1,f*lado);
			glTexCoord2f(1, 0);
			glVertex3f(i * lado, 0.1, f * lado + lado);
			glTexCoord2f(1, 1);
			glVertex3f(i * lado + lado,0.1, f * lado + lado);
			glTexCoord2f(0, 1);
			glVertex3f(i * lado + lado, 0.1, f * lado);
			glEnd();
		}
	}
	glPopMatrix();
}

void desenhaArvore() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_tronco_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_tronco_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_tronco_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_tronco_shininess);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Arvfrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Arvesq);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Arvdir);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Arvtras);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_verduras_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_verduras_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_verduras_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_verduras_shininess);
	desenha_chao();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, FolhaBaixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Folhafrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Folhaesq);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Folhadir);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Folhatras);
	glDisable(GL_TEXTURE_2D);
}

void desenhachuva() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_agua_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_agua_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_agua_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_agua_shininess);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 0; i < 1024; i++) {
		glPushMatrix();
		glTranslatef(chuva_x[i], chuva_y[i], chuva_z[i]);
		chuva_y[i] = chuva_y[i] - 0.1;
		if (chuva_y[i] <= 0) {
			chuva_y[i] = 5;
		}
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Chuva);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, Chuva_inv);
		glPopMatrix();
	}
	glBlendFunc(GL_ONE, GL_ZERO);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	//viewport pequeno
	glViewport(0, 0, wScreen * 0.25, 0.25 * hScreen);//Ocupa o 1/4 ecrã
	glMatrixMode(GL_PROJECTION); //matriz da projeção
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW); //matriz das trasformações
	glLoadIdentity();
	gluLookAt(0, 3, 0, 0, 0, 0, 0, 0, -1);
	//objetos
	iluminacao();
	desenhaCarro();
	desenhaArvore();
	//viewport grande
	glViewport(wScreen * 0, 0, wScreen , hScreen);
	glMatrixMode(GL_PROJECTION); //matriz da projeção
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 999);
	glMatrixMode(GL_MODELVIEW); //matriz das trasformações
	glLoadIdentity();
	gluLookAt(5, tam * 2 + 0.1, 5, 0, tam * 2 + 0.1, 0, 0, 1, 0);
	//objetos
	iluminacao();
	desenhaCarro();
	desenhaArvore();
	desenhachuva();
	//---------------------
	glutSwapBuffers();
}

float aleatorio(GLint minimo, GLint maximo) {
	GLfloat y;
	y = rand() % 1000;
	return (minimo + 0.001 * y * (maximo - minimo));
}


void inicia_chuva() {
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 32; i++) {
			chuva_x[32 * j + i] = aleatorio(-5, 5);
			chuva_z[32 * j + i] = aleatorio(-5, 5);
			chuva_y[32 * j + i] = aleatorio(0, 5);
		}
	}
}

void Timer(int value)
{
	angulo_rodar = angulo_rodar + angulo_inc;
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

void teclasascii(unsigned char key, int x, int y) {
	switch (key) {
	case ('s'):
		diracaoLuz2[0] = 0;
		diracaoLuz2[2] = 1;
		glutPostRedisplay();
		break;
	case ('d'):
		diracaoLuz2[0] = 1;
		diracaoLuz2[2] = 0;
		glutPostRedisplay();
		break;
	case ('a'):
		diracaoLuz2[0] = -1;
		diracaoLuz2[2] = 0;
		glutPostRedisplay();
		break;
	case ('w'):
		diracaoLuz2[0] = 0;
		diracaoLuz2[2] = -1;
		glutPostRedisplay();
		break;
	case ('m'):
		tipo_mat = (tipo_mat + 1) % 2;
		glutPostRedisplay();
		break;
	case('p'):
		polig= (polig+1)%3;
		if (polig == 0) {
			quads = 100;
		}
		else if(polig == 1)
		{
			quads = 200;
		}
		else
		{
			quads = 400;
		}
		glutPostRedisplay();
		break;
	case ('t'):
		transp = (transp + 1) % 2;
		if (transp) {
			material_agua_diffuse[3] = 0.4;
		}
		else {
			material_agua_diffuse[3] = 1;
		}
		glutPostRedisplay();
		break;
	case ('i'):
		intensidade = (intensidade + 1) % 2;
		if (intensidade) {
			for (int i = 0; i < 3; i++) {
				corAmbLuz1[i] = corAmbLuz1[i] / 3.0;
				corDifLuz1[i] = corDifLuz1[i] / 3.0;
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				corAmbLuz1[i] = corAmbLuz1[i] * 3.0;
				corDifLuz1[i] = corDifLuz1[i] * 3.0;
			}
		}
		glutPostRedisplay();
		break;
	case ('c'):
		intensidade = 1;
		cor = (cor + 1) % 2;
		if (cor) {
			for (int i = 0; i < 3; i++) {
				corAmbLuz1[i] = corDiaAmbLuz1[i];
				corDifLuz1[i] = corDiaDifLuz1[i];
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				corAmbLuz1[i] = corVermAmbLuz1[i];
				corDifLuz1[i] = corVermDifLuz1[i];
			}
		}
		glutPostRedisplay();
		break;
	}
	
}

void initTexturas() {
	//relva
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("teste_relva.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	//folha
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("nova_folha.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	//cepo
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("casca.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void initialize(void) {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	initTexturas();
	glShadeModel(GL_SMOOTH);
	inicia_chuva();
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glVertexPointer(3, GL_FLOAT, 0, posicoes);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(" Carro e Arvore ");
	initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(teclasascii);
	glutTimerFunc(msec, Timer, 1);
	glutMainLoop();
	return 1;
}