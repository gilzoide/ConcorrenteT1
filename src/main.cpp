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
	resolvedor *R = nullptr;

	// checa entradas possíveis
    for (int i = 1; i < argc; i++) {
        if (string (argv[i]) == "--multi") {
            int numberOfThreadsToUse = 0;
            if (argc > i + 2 && string (argv[++i]) == "--nthreads") {
				// bloco try/catch ignora erros do `stoi` (tipo um não número)
				try {
	                numberOfThreadsToUse = stoi (string (argv[++i]));
				}
				catch (...) {}
            } 
            R = new resolvedorMultithread (MA, MB, numberOfThreadsToUse);
			break;
    	}
    }

	// ou sequencial mesmo
	if (!R) {
		R = new resolvedor (MA, MB);
	}

	R->resolva (linhaTeste, erro, maxIter);

	delete R;

	return 0;
}
