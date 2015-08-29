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
	 * @return Diferença entre maior valor de `aux' e MB
	 */
	virtual void itera (double *atual, double *aux);

	/// Matriz A (quadrada)
	matrizQuadrada& MA;
	/// Matriz B (o vetor)
	matriz& MB;
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
};
