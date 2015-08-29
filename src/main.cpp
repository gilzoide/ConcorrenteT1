#include "matriz.hpp"
#include "resolvedor.hpp"

#include <cstring>

int main (int argc, char *argv[]) {

	// ordem da matriz (quadrada)
	unsigned int ordem;
	cin >> ordem;
	cout << "ordem = " << ordem << endl;

	// fila a ser avaliada
	int linhaTeste;
	cin >> linhaTeste;
	cout << "linhaTeste = " << linhaTeste << endl;
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
	MA.read ();

	// nossa matriz B, o vetor
	matriz MB (1, ordem);
	MB.read ();

	// agora só falta resolver xD
	resolvedor *R;
	cout << endl << "Resolução ";
	// concorrente
	if (argc > 1 && strcmp (argv[1], "multi") == 0) {
		cout << "multithread";
		R = new resolvedorMultithread (MA, MB);
	}
	// ou sequencial mesmo
	else {
		cout << "singlethread";
		R = new resolvedor (MA, MB);
	}
	cout << " escolhida" << endl << endl;
	R->resolva (linhaTeste, erro, maxIter);

	delete R;

	return 0;
}
