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
	 */
	virtual void resolva ();

protected:
	/**
	 * Função que normaliza um sistema linear, dividindo cada linha
	 * pelo coeficiente da diagonal da MA
	 */
	void normalizaSistema ();

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
	resolvedorMultithread (matrizQuadrada& MA, matriz& MB);
};
