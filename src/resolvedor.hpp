#pragma once

#include "matriz.hpp"
#include <pthread.h>

/**
 * Resolvedor de sistemas lineares, resolução sequencial
 */
class resolvedor {
public:
	/**
	 * Ctor com parâmetros: matrizes do sistema
	 */
	resolvedor (matrizQuadrada& MA, matriz& MB);
	/**
	 * Dtor
	 */
	virtual ~resolvedor ();

	/**
	 * Por favor, resolvedor, resolva esse sistema linear!
	 *
	 * @param[in] linhaTeste Linha a ser testada (pra comprovar que funcionou)
	 * @param[in] erro Erro permitido
	 * @param[in] maxIter Número máximo de iterações permitidas (pra não rodar infinito)
	 */
	void resolva (unsigned int linhaTeste, double erro, unsigned int maxIter);

protected:
	/**
	 * Processa as linhas do sistema, iterando 
	 *
	 * Itera sobre linhas do sistema, salvando resultados em `results', utilizando o
	 * vetor auxiliar da iteração passada.
	 *
	 * @param[in] erro Erro permitido
	 * @param[in] maxIter Número máximo de iterações permitidas
	 * @param[out] results Vetor auxiliar que contém valores da iteração atual
	 * @param aux Vetor auxiliar que contém valores da iteração passada
	 *
	 * @return Diferença entre maior valor de `aux' e MB
	 */
	virtual unsigned int processaTodasLinhas (double *results, double *aux);

	/**
	 * Processa uma linha, operação base da iteração
	 *
	 * @param[in] i Índice da linha a ser processada
	 * @param[out] atual Vetor auxiliar que contém valores da iteração atual
	 * @param[in] aux Vetor auxiliar que contém valores da iteração passada
	 */
	void processaLinha (unsigned int i, double *atual, double *aux);

	/// Matriz A (quadrada)
	matrizQuadrada& MA;
	/// Matriz B (o vetor)
	matriz& MB;
	/// Ordem do sistema, usado várias vezes por aí
	unsigned int ordem;
	/// Erro permitido
	double erro;
	/// Número máximo de iterações permitidas
	unsigned int maxIter;
};


/**
 * Resolvedor de sistemas lineares, resolução concorrente,
 * usando múltiplos threads (que fica beeeeeem mais rápido xD)
 */
class resolvedorMultithread : public resolvedor {
public:
	/**
	 * Ctor, chama o pai
	 */
	resolvedorMultithread (matrizQuadrada& MA, matriz& MB, int numberOfThreads);

protected:
	unsigned int processaTodasLinhas (double *results, double *aux) override;
};
