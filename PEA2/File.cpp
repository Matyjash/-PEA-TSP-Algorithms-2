#include "File.h"
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>


void File::getAllNumbers(std::ifstream& file) {
	if (file.is_open()) {
		bool first = true;
		std::string line;
		int number;
		int size = 1;
		int i = 0;
		do {
			std::getline(file, line);
			if (file.fail()) {
				return;
			}
			if (!line.empty()) {
				std::istringstream iss(line);
				if (first) {
					if (!(iss >> size)) return;
					size *= size;
					first = false;
				}
				while (iss >> number) {
					if (iss.fail()) return;
					else {
						listOfNumbers.push_back(number);
						i++;
					}
				}
			}
		} while (i < size);
	}
	return;
}

void File::loadGraphFromFile(Graph* gml, std::string fileName) {

	std::ifstream file;
	file.open(fileName);

	getAllNumbers(file);
	/*for (int i = 0; i < (int)listOfNumbers.size(); i++) {
		std::cout << listOfNumbers[i];
	}*/

	// listOfNumbers[0] - liczba miast
	int numberOfCities = (int)sqrt(listOfNumbers.size());
	//std::cout << "Number of cities: " << numberOfCities << "\n";
	gml->deleteMatrix();

	Graph* graph = new Graph(numberOfCities, 0, 0);

	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < numberOfCities; j++)
		{
			//std::cout << "Adding " << i << "->" << j << "[" << i + j << "]" << "\n";
			graph->addEdge(i, j, listOfNumbers[i * numberOfCities + j]);
		}
	}

	*gml = *graph;

}



