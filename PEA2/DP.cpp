#include "DP.h"
#include <iostream>

void DP::printPath() {

	int set = (1 << graph->getSize()) - 1;

	for (int j = 0; j < graph->getSize() - 1; j++) {
		int node = 0;
		int node2 = 0;
		int minimumSet;
		int minimum = INT_MAX;
		for (int i = 0; i < graph->getSize(); i++) {
			int cost = INT_MAX;
			int newSet = set & (((1 << graph->getSize()) - 1) - (1 << i));
			if (newSet != set) {

				if (matrix[newSet][i] != -1) cost = matrix[newSet][i];

				if (cost < minimum) {
					minimumSet = newSet;
					node = i;
					minimum = cost;
				}

			}

		}
		node2 = node;
		std::cout << node << " ";
		set = minimumSet;
	}
}

void DP::printMatrix() {
	for (int i = 0; i < combNumber; i++) {
		for (int j = 0; j < graph->getSize(); j++) {
			std::cout << matrix[i][j] << "\t\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void DP::findPath(Graph* graph) {

	this->graph = graph;
	combNumber = 1 << graph->getSize();
	int startSet = (1 << graph->getSize()) - 1;

	//inicjalizacja macierzy
	matrix = new int* [combNumber];
	for (int i = 0; i < combNumber; i++) {
		matrix[i] = new int[graph->getSize()];
	}

	//pierwszy rz¹d wype³niamy wartoœciamy dróg do 0
	for (int i = 0; i < graph->getSize(); i++) {
		matrix[0][i] = graph->getMatrix()[0][i];
	}

	//wype³enienie jej wartosciami INT_MAX (umownie nieskonczonosc)
	for (int i = 1; i < combNumber; i++) {
		for (int j = 0; j < graph->getSize(); j++) {
			matrix[i][j] = -1;
		}
	}

	std::cout << "\n";
	std::cout << "Dlugosc optymalnej sciezki:" << DPRec(startSet, 0);
	std::cout << "\n";
	printPath();
}

int DP::DPRec(int set, int node) {
	//koszt rozpatrywanej sciezki
	int cost;
	//minimum do odszukania najlepszej sciezki
	int minimum = INT_MAX;
	//je¿eli znamy ju¿ drogê to pobieramy j¹ bezpoœrednio z tablicy
	if (matrix[set][node] != -1) {
		return matrix[set][node];
	}
	//je¿eli nie to sprawdzamy kolejne opcje przechodz¹c przez mo¿liwe wierzcho³ki
	else {
		for (int i = 0; i < graph->getSize(); i++) {
			//usuwamy z zestawu wierzcholkow ten dla ktorego droge bedziemy liczyc
			//najpierw od pelnego zestawu (1111...) odejmujemy rozpatrywany wierzcholek i wykonujemy koniunkcje 
			//ze starym zestawem w ten sposób uzyskuj¹c ten sam zestaw ale pozbawiony rozpatrywanego wierzcholka
			int newSet = set & (((1 << graph->getSize()) - 1) - (1 << i));
			if (newSet != set) {
				//obliczamy rekurencyjnie koszt uwzgledniajac przejscie z node do i
				cost = DPRec(newSet, i) + graph->getMatrix()[node][i];
				//jezeli jest to najlepsze polaczenie to ustawiamy je jako minimum i zapisujemy w tablicy
				if (cost < minimum) {
					matrix[set][node] = cost;
					minimum = cost;
				}

			}

		}
		//zwracamy otrzymany koszt
		return matrix[set][node];
	}

}




DP::~DP() {

	for (int i = 0; i < combNumber; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}