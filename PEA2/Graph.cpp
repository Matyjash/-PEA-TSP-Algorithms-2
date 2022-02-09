#include "Graph.h"
#include <climits>
#include <iostream>
#include <algorithm>
#include "File.h"


Graph::Graph(int size, int startNode, int endNode) {
	setInitials(size, startNode, endNode);
}


void Graph::fillMatrix(int** matrixToFill, int sizeOfMatrix, int value) {

	for (int i = 0; i < sizeOfMatrix; i++) {
		for (int j = 0; j < sizeOfMatrix; j++) {
			matrixToFill[i][j] = value;
		}
	}
}

void Graph::resizeMatrix(int newSize) {
	int** newMatrix;								// tworzymy nowa macierz
	newMatrix = new int* [newSize];					// inicjujemy j¹
	for (int i = 0; i < newSize; i++) {
		newMatrix[i] = new int[newSize];
	}
	fillMatrix(newMatrix, newSize, INT_MAX);		// wypelniamy MAX_INT'ami (umownie brak krawêdzi)

	for (int i = 0; i < size && i < newSize; i++) {	// przepisujemy wartoœci ze starej macierzy
		for (int j = 0; j < size && j < newSize; j++) {
			newMatrix[i][j] = matrix[i][j];
		}
	}

	deleteMatrix();									// usuwamy star¹ macierz

	size = newSize;									// nadpisujemy rozmiar nowym rozmiarem
	matrix = newMatrix;								// nadpisujemy star¹ macierz now¹ macierz¹
	return;
}

void Graph::addEdge(int x, int y, int weight) {

	if (x >= 0 && x < size && y >= 0 && y < size) {	// je¿eli wspó³rzêdne s¹ prawid³owe
		if (matrix[x][y] == INT_MAX) edges++;
		matrix[x][y] = weight;						// wstawiamy wagê w odpowiednie miejsce
		//std::cout << "\nDodano krawedz na wspolrzednych x="<< x <<" y="<< y <<" o wadze=" << weight << "\n"; 
	}
	else {											// w przeciwnym wypadku publikujemy odpowiedni komunikat
		std::cout << "\nWprowadzono wartosc spoza zakresu maceirzy!\n";
	}
	return;
}

void Graph::deleteEdge(int x, int y) {
	if (x >= 0 && x < size && y >= 0 && y < size) {	// je¿eli wspórzêdne s¹ prawid³owe
		matrix[x][y] = INT_MAX;						// wstawiamy umowny brak krawedzi w odpowienie miejsce
		//std::cout << "\nUsunieto krawedz na wspolrzednych x=" << x << " y=" << y << "\n";
	}
	else {											// w przeciwnym wypadku publikujemy odpowiedni komunikat
		std::cout << "\nWprowadzono wartosc spoza zakresu maceirzy!\n";
	}
	return;
}

void Graph::printGraphMatrix() {
	for (int i = 0; i < size; i++) {
		std::cout << "  " << i;
	}
	std::cout << "\n";
	for (int i = 0; i < size; i++) {
		std::cout << i;
		for (int j = 0; j < size; j++) {

			if (matrix[i][j] != INT_MAX) std::cout << " " << matrix[i][j] << " ";
			else std::cout << "   ";
		}
		std::cout << "\n";
	}

	return;
}

int Graph::getSize() {
	return size;
}

int** Graph::getMatrix() {
	return matrix;
}

int Graph::getStartNode() {
	return startNode;
}

int Graph::getEndNode() {
	return endNode;
}

int Graph::getNumberOfEdges() {
	return edges;
}
void Graph::deleteMatrix() {

	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	size = 0;
}

void Graph::setInitials(int size, int startNode, int endNode) {
	this->size = size;								// nadpisujemy rozmiar macierzy
	matrix = new int* [size];						// inicjujemy macierz
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	fillMatrix(matrix, size, INT_MAX);				// wype³niamy j¹ wartoœci¹ MAX_INT (umownie brak krawêdzi)

	this->startNode = startNode;
	this->endNode = endNode;
}

void Graph::loadGraphFromFile(std::string fileName) {
	File file;
	file.loadGraphFromFile(this, fileName);
}

int Graph::reduceMatrix() {
	int sumCost = 0;
	//bierzemy kolejne wiersze
	for (int i = 0; i < size; i++) {
		int minimum = INT_MAX;
		//znajdujemy minimalny element we wierszu
		for (int j = 0; j < size; j++) {
			if (i != j && matrix[i][j] < minimum) {
				minimum = matrix[i][j];
			}
		}
		if (minimum != INT_MAX) sumCost += minimum;
		//redukujemy wartoœci w wierszu o minimum (poza tymi o wartosci 0/INT_MAX)
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] != INT_MAX && matrix[i][j] != 0)
				matrix[i][j] -= minimum;
		}
	}

	//bierzemy kolejne kolumny
	for (int i = 0; i < size; i++) {
		int minimum = INT_MAX;
		//znajdujemy minimalny element w kolumnie
		for (int j = 0; j < size; j++) {
			if (i != j && matrix[j][i] < minimum) {
				minimum = matrix[j][i];
			}
		}
		if (minimum != INT_MAX)
			sumCost += minimum;
		//redukujemy wartoœci w koluknie o minimum (poza tymi o wartosci 0/INT_MAX)
		for (int j = 0; j < size; j++) {
			if (matrix[j][i] != INT_MAX && matrix[j][i] != 0)
				matrix[j][i] -= minimum;
		}
	}
	return sumCost;
}

void Graph::reduceColumnsAndRows(int rowNumber, int columnNumber) {

	for (int i = 0; i < size; i++) {
		matrix[rowNumber][i] = INT_MAX;
		matrix[i][columnNumber] = INT_MAX;
	}

	//droga w drug¹ stonê równie¿ na INT_MAX
	matrix[columnNumber][rowNumber] = INT_MAX;
	matrix[columnNumber][0] = INT_MAX;

}


void Graph::clone(Graph* graph) {
	deleteMatrix();
	setInitials(graph->getSize(), graph->getStartNode(), graph->getEndNode());

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = graph->getMatrix()[i][j];
		}
	}
}


Graph::~Graph() {
	deleteMatrix();
}