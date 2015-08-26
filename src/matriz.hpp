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
	matriz (int ordem);
	/**
	 * Dtor
	 */
	~matriz ();

	/// Ordem da matriz
	int ordem;
	int **mat;
};
