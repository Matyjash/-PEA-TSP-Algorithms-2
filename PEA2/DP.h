#pragma once
#include "Graph.h"
#include <vector>
#include <math.h>
#include <string>

class DP
{
private:
	int** matrix;
	Graph* graph;
	int combNumber;
public:



	/// <summary>
	/// Szukanie optymalnej œcie¿ki w grafie dla problemu TSP sposobem DP
	/// Inicjalizacja tablicy 
	/// </summary>
	/// <param name="graph"></param>
	void findPath(Graph* graph);

	int DPRec(int set, int node);

	void printPath();

	void printMatrix();

	~DP();

};

