#include "matriz.hpp"

/**
 * Função que normaliza um sistema linear, dividindo cada linha
 * pelo coeficiente da diagonal da MA
 */
void normalizaSistema (matrizQuadrada& MA, matriz& MB) {
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


int main () {
	// ordem da matriz (quadrada)
	unsigned int ordem;
	cin >> ordem;
	cout << "ordem = " << ordem << endl;

	// fila a ser avaliada
	int fila;
	cin >> fila;
	cout << "fila = " << fila << endl;
	// erro permitido
	float erro;
	cin >> erro;
	cout << "erro = " << erro << endl;
	// número máximo de iterações
	float maxIter;
	cin >> maxIter;
	cout << "maxIter = " << maxIter << endl;


	// nossa matriz quadrada de inteiros
	matrizQuadrada MA (ordem);

	// lê matriz quadrada
	MA.read ();

	cout << endl << "MA:" << endl;
	MA.print ();

	// nossa matriz B, o vetor
	matriz MB (ordem, 1);
	MB.read ();

	cout << endl << "MB:" << endl;
	MB.print ();

	// normaliza o sistema, pra diagonal de MA ter sempre coeficiente 1
	normalizaSistema (MA, MB);
	cout << endl << "MA normalizada:" << endl;
	MA.print ();
	cout << endl << "MB normalizada:" << endl;
	MB.print ();

	return 0;
}
