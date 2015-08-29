#pragma once

#include <iostream>

using namespace std;

/**
 * Classe que representa uma matriz, com suas operações importantes
 */
class matriz {
public:
	/**
	 * Ctor com parâmetro: altura e largura da matriz
	 */
	matriz (unsigned int altura, unsigned int largura);
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
	double *operator[] (unsigned int indice);

	/**
	 * Lê uma matriz da stdin
	 */
	void read ();
	/**
	 * Imprime matriz, função para debug
	 */
	void print ();

protected:
	/// Altura da matriz
	unsigned int altura;
	/// Largura da matriz
	unsigned int largura;
	/// A matriz de dados, em si
	double **mat;
};

/**
 * Classe que representa uma matriz quadrada, com suas operações diferentes
 */
class matrizQuadrada : public matriz {
public:
	/**
	 * Ctor com parâmetro: ordem da matriz
	 */
	matrizQuadrada (unsigned int ordem);
private:
};
