#include "matriz.hpp"
#include <cstdlib>

matriz::matriz (unsigned int altura, unsigned int largura) : 
   		altura (altura), largura (largura) {
	if (altura && largura) {
		mat = new double[altura * largura];
	}
}


matriz::~matriz () {
	if (mat) {
		delete[] mat;
	}
}


double *matriz::operator[] (unsigned int indice) {
	return indice < altura ? mat + (indice * largura) : nullptr;
}


double matriz::getAltura () {
	return altura;
}


double matriz::getLargura () {
	return largura;
}


void matriz::print () {
	for (unsigned int i = 0; i < altura; i++) {
		for (unsigned int j = 0; j < largura; j++) {
			cout << mat[i * largura + j] << ' ';
		}
		cout << endl;
	}
}


void matriz::read () {
	for (unsigned int i = 0; i < altura; i++) {
		for (unsigned int j = 0; j < largura; j++) {
			cin >> mat[i * largura + j];
		}
	}
}

/* Específicos de matrizQuadrada */
matrizQuadrada::matrizQuadrada (unsigned int ordem) : matriz (ordem, ordem) {}


unsigned int matrizQuadrada::getOrdem () {
	return altura;
}
