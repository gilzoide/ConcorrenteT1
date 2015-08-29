#include "matriz.hpp"

matriz::matriz (unsigned int altura, unsigned int largura) : 
   		altura (altura), largura (largura) {
	if (altura && largura) {
		mat = new double* [altura];
		for (unsigned int i = 0; i < altura; i++) {
			mat[i] = new double[largura];
		}
	}
}


matriz::~matriz () {
	for (unsigned int i = 0; i < altura; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}


double *matriz::operator[] (unsigned int indice) {
	return indice < altura ? mat[indice] : nullptr;
}


void matriz::print () {
	for (unsigned int i = 0; i < altura; i++) {
		for (unsigned int j = 0; j < largura; j++) {
			cout << mat[i][j] << ' ';
		}
		cout << endl;
	}
}


void matriz::read () {
	for (unsigned int i = 0; i < altura; i++) {
		for (unsigned int j = 0; j < largura; j++) {
			cin >> mat[i][j];
		}
	}
}

/* Específicos de matrizQuadrada */
matrizQuadrada::matrizQuadrada (unsigned int ordem) : matriz (ordem, ordem) {}
