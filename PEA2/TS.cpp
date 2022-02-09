#include "TS.h"
#include "Random.h"
#include <windows.h>
#include <time.h>
#include <iostream>
#include <math.h>>
#include <algorithm>
#include <random>
#include <iomanip>


void TS::printPath(std::vector<int> path) {
	std::cout << "\n";
	std::cout << "0->";
	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i] << "->";
	}
	std::cout << "0\n";

}

long long int TS::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

std::vector<int> TS::generateRandomPath() {
	std::vector<int> path;

	//tworzymy liste zawieraj�c� numery wszystkich miast (opr�cz 0)
	for (int i = 1; i < graph->getSize(); i++) {
		path.push_back(i);
	}

	std::random_shuffle(path.begin(), path.end());

	return path;
}

void TS::swapTwoRandomCities(std::vector<int>* path) {
	//metoda analogiczna do tej z SA, z t� r�nic�, �e sprawdzamy czy wygenerowana zmiana nie znajduje si�
	//w tablicy tabu

	int city1Index;
	int city2Index;

	do {
		city1Index = Random::generateRandomNumber(0, graph->getSize() - 1);
		city2Index = Random::generateRandomNumber(0, graph->getSize() - 1);
		while (city1Index == city2Index) {
			city2Index = Random::generateRandomNumber(0, graph->getSize() - 1);
		}
	} while (tabuArray[city1Index][city2Index]);

	std::swap((*path)[city1Index], (*path)[city2Index]);
	tabuArray[city1Index][city2Index] = true;
	tabuArray[city2Index][city1Index] = true;
	return;
}

void TS::swapTwoBestRandomCities(std::vector<int>* path, int minSearchLength, int maxSearchLength, int plusLength, int aspiration) {
	//czy osi�gneli�my aspiracj�
	bool aspirationReached = false;
	//index miast do zamiany
	int city1Index;
	int city2Index;
	//najlepsze znalezione rozwi�zanie
	int bestCost = INT_MAX;
	std::vector<int> bestPath;
	//zamienione indexy dla najlepszego rozwi�zania
	int index1Changed;
	int index2Changed;

	for (int i = 0; i < maxSearchLength; i++)
	{
		//kopia �cie�ki dostarczonej funkcji
		std::vector<int> newPath = *path;
		do {
			//losujemy 2 r�ne indexy
			city1Index = Random::generateRandomNumber(0, graph->getSize() - 1);
			city2Index = Random::generateRandomNumber(0, graph->getSize() - 1);
			while (city1Index == city2Index) {
				city2Index = Random::generateRandomNumber(0, graph->getSize() - 1);
			}
			//dop�ki nie znajdziemy takiej zmiany kt�ra nie jest w tablicy tabu
		} while (tabuArray[city1Index][city2Index]);
		//dokonujemy zamiany dla wylosowanych index�w
		std::swap((newPath)[city1Index], (newPath)[city2Index]);
		//je�eli �cie�ka jest najlepsz� z do tej pory wylosowanych to zapisujemy j� jako najelpsz�
		if (getPathCost(newPath) < bestCost) {
			bestPath = newPath;
			bestCost = getPathCost(bestPath);
			index1Changed = city1Index;
			index2Changed = city2Index;
			//je�eli osi�gn�li�my aspiracj�
			if (getPathCost(newPath) < aspiration) {
				aspirationReached = true;
			}
		}
		//je�eli aspiracja zosta�a wcze�niej osi�gni�ta do odliczamy do ko�ca (plusLength) i ko�czymy je�eli osi�gn�lismy minSearchLength
		if (aspirationReached) {
			if (plusLength == 0 && i>=minSearchLength) break;
			plusLength--;
		}
		
	}

	*path = bestPath;
	lastChangedIndex1 = index1Changed;
	lastChangedIndex2 = index2Changed;

	return;
}

void TS::clearTabuArray() {
	for (int i = 0; i < graph->getSize(); i++) {
		for (int j = 0; j < graph->getSize(); j++) {
			tabuArray[i][j] = false;
		}
	}
}

int TS::getPathCost(std::vector <int> path) {
	int cost = 0;
	//dodajemy koszt przejscia z mista 0 do pierwszego w �cie�ce
	cost += graph->getMatrix()[0][path[0]];
	//dodajemy koszty przej�� w �cie�ce
	for (unsigned int i = 0; i < path.size() - 1; i++) {
		cost += graph->getMatrix()[path[i]][path[i + 1]];
	}
	//dodajemy koszt przejscia z miasta ostatniego do 0
	cost += graph->getMatrix()[path[path.size() - 1]][0];

	return cost;
}

std::vector<int> TS::generateInitialPath() {
	//metoda to�sama z t� przedstawion� w SA
	bool* visited = new bool[graph->getSize()];
	visited[0] = true;
	for (int i = 1; i < graph->getSize(); i++) {
		visited[i] = false;
	}
	std::vector<int> path;
	path.push_back(0);

	int minimumNode = 0;

	for (int i = 1; i < graph->getSize(); i++) {
		int minimumCost = INT_MAX;
		for (int j = 1; j < graph->getSize(); j++) {
			if (!visited[j] && graph->getMatrix()[path[path.size() - 1]][j] < minimumCost) {
				minimumNode = j;
				minimumCost = graph->getMatrix()[path[path.size() - 1]][j];
			}
		}
		path.push_back(minimumNode);
		visited[minimumNode] = true;
	}

	path.erase(path.begin());
	delete[] visited;
	return path;

}

void TS::search(Graph* graph, int timeToStop,bool diversification) {
	this->graph = graph;
	int searchLength = graph->getSize();
	int noChangeInterationCount = 0;

	//tworzymy tablice tabu i inicjalizujemy j�
	tabuArray = new bool* [graph->getSize()];
	for (int i = 0; i < graph->getSize(); ++i)
		tabuArray[i] = new bool[graph->getSize()];
	//ustawiamy wszystkie warto�ci na false
	clearTabuArray();

	//funkcje zwi�zane z pomiarem czasu
	srand(time(NULL));
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	TS::startTime = read_QPC();

	//pocz�tkowe rozwi�zanie
	std::vector<int> path = generateInitialPath();
	std::vector<int> bestPath = path;
	int bestCost = getPathCost(path);

	//liczenie czasu
	long long int timeSpent = 0;


	while (timeSpent < timeToStop) {
		//dokonujemy zamiay zgodnie z poni�sz� metod� i przekazanymi jej parametrami
		swapTwoBestRandomCities(&path, 20, 100,10,getPathCost(path));

		//je�eli zmiana poprawia �cie�k� to przyjmujemy j� jako now� najlepsz�
		if (getPathCost(path) < bestCost) {
			//std::cout << "\n New best\n";
			bestCost = getPathCost(path);
			bestPath = path;
			noChangeInterationCount = 0;
			//aktualizujemy tablic� tabu
			tabuArray[lastChangedIndex1][lastChangedIndex2] = true;
		}
		else {
			//je�eli nie dosz�o do zmiany �cie�ki to zwi�kszamy licznik
			noChangeInterationCount++;
		}

		if (diversification) {
			//je�eli nie zasz�a �adna zmiana przez x iteracji to generujemy losow� �cie�k� i przyjmujemy j� jako aktualn�
			//oraz czy�cimy tablic� tabu
			if (noChangeInterationCount == 10000) {
				path = generateRandomPath();
				noChangeInterationCount = 0;
				clearTabuArray();
			}
		}
		//aktualizacja czasu
		timeSpent = ((read_QPC() - startTime) / frequency);
	}


	//czyszczenie tablicy tabu
	for (int i = 0; i < graph->getSize(); ++i) {
		delete[] tabuArray[i];
	}
	delete[] tabuArray;

	std::cout << "Odnaleziona sciezka: \n";
	printPath(bestPath);
	std::cout << "Koszt: "<<getPathCost(bestPath)<<"\n";
	std::cout << "Czas: " << timeSpent<<" s\n";
	
}