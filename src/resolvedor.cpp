#include "resolvedor.hpp"

resolvedor::resolvedor (matrizQuadrada& MA, matriz& MB) : MA (MA), MB (MB) {}


resolvedor::~resolvedor () {}


void resolvedor::normalizaSistema () {
	auto ordem = MA.getOrdem ();
	for (unsigned int i = 0; i < ordem; i++) {
		auto divisor = MA[i][i];
		// divide MA
		for (unsigned int j = 0; j < ordem; j++) {
			MA[i][j] /= divisor;
		}
		// divide MB
		MB[i][0] /= divisor;
	}
}


void resolvedor::resolva (unsigned int linhaTeste, double erro, unsigned int maxIter) {
	normalizaSistema ();
	cout << endl << "MA normalizada:" << endl;
	MA.print ();
	cout << endl << "MB normalizada:" << endl;
	MB.print ();
}

/* Específicos de resolvedorMultithread */
resolvedorMultithread::resolvedorMultithread (matrizQuadrada& MA, matriz& MB) :
		resolvedor (MA, MB) {}


void resolvedorMultithread::resolva (unsigned int linhaTeste, double erro, 
		unsigned int maxIter) {
	normalizaSistema ();
	cout << endl << "MA normalizada:" << endl;
	MA.print ();
	cout << endl << "MB normalizada:" << endl;
	MB.print ();
}
