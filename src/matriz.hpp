#pragma once

#include <iostream>

using namespace std;

/**
 * Classe que representa uma matriz quadrada, com suas operações importantes
 */
class matriz {
public:
	/**
	 * Ctor com parâmetro: ordem da matriz
	 */
	matriz (unsigned int ordem);
	/**
	 * Dtor
	 */
	~matriz ();

	/**
	 * Get Linha[indice]
	 *
	 * @note Como 
	 *
	 * @param[in] indice Índice da linha desejada
	 *
	 * @return Linha da matriz, nullptr se fora de ordem
	 */
	int *operator[] (unsigned int indice);

	/**
	 * Imprime matriz, função para debug
	 */
	void print ();

	/// Ordem da matriz
	unsigned int ordem;
	/// A matriz de dados, em si
	int **mat;
};
