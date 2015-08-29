#include "resolvedor.hpp"
#include <cstring>
#include <cmath>

resolvedor::resolvedor (matrizQuadrada& MA, matriz& MB) : MA (MA), MB (MB) {}


resolvedor::~resolvedor () {}


/**
 * Função auxiliar que acha o maior diferença entr valores de `v1' e `v2'
 */
double achaMaiorDiferenca (const double *v1, const double *v2, size_t tamanho) {
	double ret = 0;
	for (unsigned int i = 0; i < tamanho; i++) {
		auto aux = fabs (v1[i] - v2[i]);
		if (aux > ret) {
			ret = aux;
		}
	}

	return ret;
}


void resolvedor::resolva (unsigned int linhaTeste, double erro, unsigned int maxIter) {
	// ordem da matriz, que é usada algumas vezes por aí
	auto ordem = MA.getOrdem ();

	// vetor de resultados, dados pela próxima iteração
	double results[ordem];
	memcpy (results, MB[0], sizeof results);
	// vetor auxiliar, que guarda os passos de iteração já executados
	double aux[ordem];

	unsigned int i;
	for (i = 0; i < maxIter; i++) {
		// aux segura os valores da iteração anterior
		memcpy (aux, results, sizeof aux);
		// resolve uma iteração (que será multithreaded no resolvedorMultithread)
		itera (results, aux);

		double diferenca = achaMaiorDiferenca (results, aux, ordem);
		if (diferenca < erro) {
			break;
		}
	}

	// saída esperada
	cout << "Iterations: " << i << endl;

	// resultado teste, pra comparar se método funcionou
	double teste = 0;
	for (i = 0; i < ordem; i++) {
		teste += MA[linhaTeste][i] * results[i];
	}

	cout << "RowTest: " << linhaTeste << " => [" << teste << "] =? " 
			<< MB[0][linhaTeste] << endl;
}


void resolvedor::itera (double *atual, double *aux) {
	auto ordem = MA.getOrdem ();

	// pra cada linha, faz a operação
	for (unsigned int i = 0; i < ordem; i++) {
		double somaColunas = 0;
		// subtrai todas as colunas, ignorando a diagonal
		for (unsigned int j = 0; j < ordem; j++) {
			if (j != i) {
				somaColunas += MA[i][j] * aux[j];
			}
		}
		atual[i] = (MB[0][i] - somaColunas) / MA[i][i];
	}
}


/* Específicos de resolvedorMultithread */
resolvedorMultithread::resolvedorMultithread (matrizQuadrada& MA, matriz& MB) :
		resolvedor (MA, MB) {}


void resolvedorMultithread::itera (double *atual, double *aux) {
}	
