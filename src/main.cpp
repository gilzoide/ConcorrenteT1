#include "matriz.hpp"
#include "resolvedor.hpp"

#include <cstring>

int main (int argc, char *argv[]) {

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

	// agora só falta resolver xD
	resolvedor *R;
	cout << endl << "Resolução ";
	// concorrente
	if (argc && strcmp (argv[1], "multi") == 0) {
		cout << "multithread";
		R = new resolvedorMultithread (MA, MB);
	}
	// ou sequencial mesmo
	else {
		cout << "singlethread";
		R = new resolvedor (MA, MB);
	}
	cout << " escolhida" << endl;
	R->resolva ();

	delete R;

	return 0;
}
