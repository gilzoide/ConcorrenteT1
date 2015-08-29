#include "matriz.hpp"

matriz::matriz (unsigned int ordem) : ordem (ordem) {
	mat = new int* [ordem];
	for (unsigned int i = 0; i < ordem; i++) {
		mat[i] = new int[ordem];
	}
}


matriz::~matriz () {
	for (unsigned int i = 0; i < ordem; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}


int *matriz::operator[] (unsigned int indice) {
	return indice < ordem ? mat[indice] : nullptr;
}


void matriz::print () {
	for (unsigned int i = 0; i < ordem; i++) {
		for (unsigned int j = 0; j < ordem; j++) {
			cout << mat[i][j] << ' ';
		}
		cout << endl;
	}
}
