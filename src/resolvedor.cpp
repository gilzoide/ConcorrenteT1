#include "resolvedor.hpp"
#include <cstring>
#include <cmath>
#include <omp.h>

resolvedor::resolvedor (matrizQuadrada& MA, matriz& MB) : MA (MA), MB (MB),
		ordem (MA.getOrdem ()) {}


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
/**
 * Outra função auxiliar
 */
double achaMaior (const double *v, size_t tamanho) {
	double ret = 0;
	for (unsigned int i = 0; i < tamanho; i++) {
		if (v[i] > ret) {
			ret = v[i];
		}
	}

	return ret;
}


void resolvedor::resolva (unsigned int linhaTeste, double erro, unsigned int maxIter) {
	this->erro = erro;
	this->maxIter = maxIter;

	// vetor de resultados, dados pela próxima iteração
	double results[ordem];
	
	unsigned int i;
	// copia 
	for (i = 0; i < ordem; i++) {
		results[i] = MB[0][i] / MA[i][i];
	}
	// vetor auxiliar, que guarda os passos de iteração já executados
	double aux[ordem];
	memcpy (aux, results, ordem * sizeof (double));

	i = processaTodasLinhas (results, aux);

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


unsigned int resolvedor::processaTodasLinhas (double *results, double *aux) {
	// pra cada iteração
	unsigned int i;
	for (i = 0; i < maxIter; i++) {
		// aux segura os valores da iteração anterior
		memcpy (aux, results, ordem * sizeof (double));
		// pra cada linha, faz a operação
		for (unsigned int j = 0; j < ordem; j++) {
			processaLinha (j, results, aux);
		}

		double diferenca = achaMaiorDiferenca (results, aux, ordem) / achaMaior (results, ordem);
		if (diferenca < erro) {
			i++;
			break;
		}
	}

	return i;
}


void resolvedor::processaLinha (unsigned int i, double *atual, double *aux) {
	double somaColunas = 0;
	// subtrai todas as colunas, ignorando a diagonal
	for (unsigned int j = 0; j < ordem; j++) {
		if (j != i) {
			somaColunas += MA[i][j] * aux[j];
		}
	}
	atual[i] = (MB[0][i] - somaColunas) / MA[i][i];
}


/*------------------- Específicos de resolvedorMultithread -------------------*/
int min (int a, int b) {
	return a < b ? a : b;
}


resolvedorMultithread::resolvedorMultithread (matrizQuadrada& MA, matriz& MB, int numberOfThreadsToUse) :
		resolvedor (MA, MB) {
	// se tem menos linhas que threads suportadas, não adianta tanta thread =P
	if (numberOfThreadsToUse > 0) {
		omp_set_num_threads (min (ordem, numberOfThreadsToUse));
	}
}


unsigned int resolvedorMultithread::processaTodasLinhas (double *results, double *aux) {
	// pra cada iteração
	unsigned int i;
	for (i = 0; i < maxIter; i++) {
		// aux segura os valores da iteração anterior
		memcpy (aux, results, ordem * sizeof (double));

		// processa linhas em multithreaded
		#pragma omp parallel for
		for (unsigned int j = 0; j < ordem; j++) {
			processaLinha (j, results, aux);
		}

		double diferenca = achaMaiorDiferenca (results, aux, ordem) / achaMaior (results, ordem);
		if (diferenca < erro) {
			i++;
			break;
		}
	}

	return i;
}
