#include "matriz.hpp"

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

	//normalizaSistema (MA, MB);

	return 0;
}
