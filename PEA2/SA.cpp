#include "SA.h"
#include <windows.h>
#include <time.h>
#include <iostream>
#include <math.h>>
#include <algorithm>
#include <random>
#include <iomanip>

void printPath(std::vector<int> path) {
	std::cout << "\n";
	std::cout << "0->";
	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i] << "->";
	}
	std::cout << "0\n";

}

long long int SA::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}


double SA::getProbabillity(int cost, int newCost, double temperature) {
	double probability = std::exp(double((double(cost) - double(newCost)) / temperature));
	return probability;
}

void SA::swapTwoRandomCities(std::vector<int>* path) {

	//generujemy dwa r�ne od siebie indexy i dokonujemy zamiany wartosci kryj�cych si� pod nimi
	int city1Index = Random::generateRandomNumber(0, graph->getSize() -1);
	int city2Index = Random::generateRandomNumber(0, graph->getSize() -1);

	while (city1Index == city2Index) {
		city2Index = Random::generateRandomNumber(0, graph->getSize() - 1);
	}

	std::swap((*path)[city1Index], (*path)[city2Index]);
}

std::vector<int> SA::generateInitialPath() {
	//tworzymy i inicjalizujemy tablice reprezentuj�c� odwiedzone wierzcho�ki
	bool* visited = new bool[graph->getSize()];
	visited[0] = true;
	for (int i = 1; i < graph->getSize(); i++) {
		visited[i] = false;
	}
	//droga kt�r� b�dziemy budowa�
	std::vector<int> path;
	path.push_back(0);
	//zaczynamy od 0
	int minimumNode = 0;
	//szukamy kolejno dla d�ugo�ci �cie�ki najkr�tsze �cie�ki aktualizuj�c drog�
	for (int i = 1; i < graph->getSize(); i++) {
		int minimumCost = INT_MAX;
		for (int j = 1; j < graph->getSize(); j++) {
			if (!visited[j] && graph->getMatrix()[path[path.size()-1]][j] < minimumCost) {
				minimumNode = j;
				minimumCost = graph->getMatrix()[path[path.size() - 1]][j];
			}
		}
		path.push_back(minimumNode);
		visited[minimumNode] = true;
	}
	//usuwamy 0 z pocz�tku poniewa� �cie�ki w obliczeniach nie uwzgl�dniaja pocz�tkowego i ko�cowego 0
	path.erase(path.begin());
	delete[] visited;
	return path;

}


float SA::updateTemperature(float oldTemperature, float alpha){
	float newTemperature = oldTemperature * alpha;
	return newTemperature;
}

std::vector<int> SA::generateRandomPath() {
	std::vector<int> path;

	//tworzymy liste zawieraj�c� numery wszystkich miast (opr�cz 0)
	for (int i = 1; i < graph->getSize(); i++) {
		path.push_back(i);
	}
	//'tasujemy' wektor
	std::random_shuffle(path.begin(), path.end());

	return path;
}

int SA::getPathCost(std::vector <int> path) {
	int cost = 0;
	//dodajemy koszt przejscia z mista 0 do pierwszego w �cie�ce
	cost += graph->getMatrix()[0][path[0]];
	//dodajemy koszty przej�� w �cie�ce
	for (unsigned int i = 0; i < path.size()-1; i++) {
		cost += graph->getMatrix()[path[i]][path[i + 1]];
	}
	//dodajemy koszt przejscia z miasta ostatniego do 0
	cost += graph->getMatrix() [path[path.size() - 1]][0];

	return cost;
}

void SA::simulateAnneling(Graph* graph, int timeToStop) {
	SA::graph = graph;

	//ilo�� zmian w �cie�ce przed aktualizacj� temperatuy
	int searchLength = graph->getSize();		
	float alpha = 0.99;
	//ALFA

	//najlepszy znaleziony do tej pory koszt i najlepsza znaleziona do tej pory droga
	int bestFoundCost = INT_MAX;
	std::vector<int> bestPath;

	//funkcje zwi�zane z pomiarem czasu
	srand(time(NULL));
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	SA::startTime = read_QPC();

	std::vector<int> path = generateInitialPath();

	int cost = getPathCost(path);


	double temperature = (cost * graph->getSize())*50;
	long long int timeSpent=0;
	//liczba iteracji

	while (timeSpent < timeToStop) {

		std::vector<int> localBest = path;
		int localBestCost = cost;
		std::vector<int> newPath; //= path;

		for(int i=0; i<searchLength; i++)
		/****ERA****/
		{
		//generujemy i �cie�ek w s�siedztwie i znajdujemy najlepsz�
		newPath = path;
		swapTwoRandomCities(&newPath);
		int newCost = getPathCost(newPath);

		if (newCost < localBestCost) {
			localBest = newPath;
			localBestCost = newCost;
		}
		}
		/***********/

		//je�eli znaleziona w erze �cie�ka jest gorsza od do tej pory znalezionej 
		//to liczymy prawdopodobie�stwo i przyjmujemy je jako aktulane je�eli r < probability
		if (localBestCost > cost) {
			double probability = getProbabillity(cost, localBestCost, temperature);
			double r = (double)Random::generateRandomNumber(0, 999) / 1000;

			if (r < probability ) {
				path = localBest;
				cost = localBestCost;
			}
			else {
			}
		}
		//je�eli znaleziona w erze �cie�ka jest lepsza to przyjmujemy ja jako aktualn�
		else {
			path = localBest;
			cost = localBestCost;
			//std::cout << "New cost: " << cost << "\n";
		}

		//aktualizujemy temperatur� oraz czas
		temperature = updateTemperature(temperature,alpha);
		timeSpent = ((read_QPC() - startTime) / frequency);

	}

	std::cout << "Odnaleziona droga: ";
	printPath(path);
	std::cout << "\nKoszt: " << cost << "\n";
	std::cout << "Czas: " << timeSpent << " s\n";

	return;



}