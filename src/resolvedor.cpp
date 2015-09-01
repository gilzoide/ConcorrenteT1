#include "resolvedor.hpp"
#include <cstring>
#include <cmath>
#include <thread>

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
resolvedorMultithread::resolvedorMultithread (matrizQuadrada& MA, matriz& MB) :
		resolvedor (MA, MB), mtx (PTHREAD_MUTEX_INITIALIZER), cond (PTHREAD_COND_INITIALIZER) {
	// se tem menos linhas que threads suportadas, não adianta tanta thread =P
	numThreads = min (ordem, thread::hardware_concurrency ());
	allThreads = new pthread_t[numThreads];

	// inicialmente, todos threads estarão trabalhando
	threadsTrabalhando = numThreads;
}


resolvedorMultithread::~resolvedorMultithread () {
	delete[] allThreads;
}


/// Struct auxiliar para chamada das pthreads
typedef struct {
	resolvedorMultithread *obj;	///< resolvedor de sistema
	unsigned int inicio, fim;	///< Índice de linha inicial e final
	double *atual, *aux;		///< Vetores auxiliares
} threadArgs;


/// Função chamada pelos threads
void *funcao (void *argumentos) {
	auto args = (threadArgs *) argumentos; // faz o cast
	args->obj->processaLinhas (args->inicio, args->fim, args->atual, args->aux);
	return NULL;
}


unsigned int resolvedorMultithread::processaTodasLinhas (double *results, double *aux) {
	// quantas linhas pra cada thread?
	int fator = ceil ((double) ordem / numThreads);

	// argumentos auxiliares, pras pthreads
	threadArgs *argumentos = new threadArgs[numThreads];
	unsigned int i;

	// prepara os argumentos comuns pra função
	for (i = 0; i < numThreads; i++) {
		argumentos[i].obj = this;
		argumentos[i].atual = results;
		argumentos[i].aux = aux;
		argumentos[i].inicio = i * fator;
		argumentos[i].fim = min ((i + 1) * fator, ordem);
		pthread_create (&allThreads[i], NULL, &funcao, &argumentos[i]);
	}
	
	// espera todos threads terminarem
	for (unsigned int i = 0; i < numThreads; i++) {
		pthread_join (allThreads[i], NULL);
	}

	delete[] argumentos;

	return iter;
}


void resolvedorMultithread::processaLinhas (unsigned int comeco, unsigned int fim,
		double *atual, double *aux) {
	while (continueTrabalhando) {
		// executa linhas
		for (auto i = comeco; i < fim; i++) {
			processaLinha (i, atual, aux);
		}

		pthread_mutex_lock (&mtx);
		threadsTrabalhando--;

		// se acabou, iteração, prepara a próxima
		if (!threadsTrabalhando) {
			iter++;

			double diferenca = achaMaiorDiferenca (atual, aux, ordem) / achaMaior (atual, ordem);
			// se acabou, seja pelo `erro' ou pelas iterações
			if (diferenca < erro || iter > maxIter) {
				continueTrabalhando = false;
			}
			else {
				// copia valores atualizados para `aux'
				memcpy (aux, atual, ordem * sizeof (double));
			}
			pthread_cond_broadcast (&cond);
			threadsTrabalhando = numThreads;
		}
		// não acabou: espera todo mundo
		else {
			pthread_cond_wait (&cond, &mtx);
		}

		pthread_mutex_unlock (&mtx);
	}
}
