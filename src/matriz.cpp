#include "matriz.hpp"

matriz::matriz (int ordem) : ordem (ordem) {
	mat = new int* [ordem];
	for (int i = 0; i < ordem; i++) {
		mat[i] = new int[ordem];
	}
}


matriz::~matriz () {
	for (int i = 0; i < ordem; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}
