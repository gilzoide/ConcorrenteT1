#include "matriz.hpp"

int main () {
	// ordem da matriz (quadrada)
	int ordem;
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
	matriz MA (ordem);

	// lê matriz quadrada
	for (int i = 0; i < ordem; i++) {
		for (int j = 0; j < ordem; j++) {
			cin >> MA[i][j];
		}
	}
	MA.print ();

	return 0;
}
