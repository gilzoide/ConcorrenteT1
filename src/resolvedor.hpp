#pragma once

#include "matriz.hpp"

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
	 * @params[in] linhaTeste Linha a ser testada (pra comprovar que funcionou)
	 * @params[in] erro Erro permitido
	 * @params[in] maxIter Número máximo de iterações permitidas (pra não rodar infinito)
	 */
	void resolva (unsigned int linhaTeste, double erro, unsigned int maxIter);

protected:
	/**
	 * Iteração da resolução do sistema linear
	 *
	 * Itera sobre linhas do sistema, salvando resultados em MB, utilizando o
	 * vetor auxiliar da iteração passada.
	 *
	 * @param[out] atual Vetor auxiliar que contém valores da iteração atual
	 * @param[in] aux Vetor auxiliar que contém valores da iteração passada
	 *
	 * @return Diferença entre maior valor de `aux' e MB
	 */
	virtual void itera (double *atual, double *aux);

	/**
	 * Processa uma linha, operação base da iteração
	 *
	 * @sa itera
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
	resolvedorMultithread (matrizQuadrada& MA, matriz& MB);
private:
	/**
	 * Versão multithread de @ref resolvedor::itera
	 */
	void itera (double *atual, double *aux) override;

	/**
	 * Função que processa mais de uma linha, pra dividir
	 * o trabalho entre os threads
	 *
	 * @param[in] comeco Índice da linha inicial
	 * @param[in] fim Índice da linha final (não inclusive)
	 * @param[out] atual Vetor auxiliar que contém valores da iteração atual
	 * @param[in] aux Vetor auxiliar que contém valores da iteração passada
	 */
	void processaLinhas (unsigned int comeco, unsigned int fim, double *atual,
			double *aux);

	/// Número de threads a serem executadas
	unsigned int numThreads{1};
};
