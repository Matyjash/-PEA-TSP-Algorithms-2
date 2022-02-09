#pragma once
#include "Graph.h"
#include <vector>
class TS
{
private:
	//graf miast
	Graph* graph;
	//indexy ostatnio zamienionych miast
	int lastChangedIndex1;
	int lastChangedIndex2;

	//czas rozpocz�cia
	long long int startTime;

	long long int frequency;

	//tablica tabu
	bool** tabuArray;

	/// <summary>
	/// Metoda wy�wietlaj�ca �cie�k�
	/// </summary>
	/// <param name="path">�cie�ka do wy�wietlenia</param>
	void printPath(std::vector<int> path);

	/// <summary>
	/// Metoda zamieniaj�ca 2 losowe miasta kolejno�ci� (je�eli ta zmiana nie znajduje si� w tablicy tabu)
	/// </summary>
	/// <param name="path">�cie�ka w kt�rej ma zosta� przeprowadzona zamiana</param>
	void swapTwoRandomCities(std::vector<int>* path);



	/// <summary>
	/// Metoda zamieniaj�ca 2 losowe miasta kolejno�ci� (je�eli ta zmiana nie znajduje si� w tablicy tabu).
	/// Metoda wyszukuje najelsze rozwi�zania spo�r�d pr�by o podanej wielko�ci
	/// </summary>
	/// <param name="path">�cie�ka w kt�rej ma zaj�� zmiana</param>
	/// <param name="minSearchLength">Minimalna d�ugo�� szukania(ilos� �cie�ek)</param>
	/// <param name="maxSearchLength">Maksymalna d�ugo�� szukania(ilos� �cie�ek)</param>
	/// <param name="plusLength">D�ugo�� szukania po znalezieniu elementu lepszego od aspiracji</param>
	/// <param name="aspiration">Warto�� kt�r� chcemy polepszy�</param>
	void swapTwoBestRandomCities(std::vector<int>* path, int minSearchLength, int maxSearchLength, int plusLength, int aspiration);

	/// <summary>
	/// Generowanie pocz�tkowej �cie�ki na podstawie kolejnych najni�szych warto�ci
	/// </summary>
	/// <returns>Wygenerowana �cie�ka</returns>
	std::vector<int> generateInitialPath();

	/// <summary>
	/// Wyliczanie kosztu przej�cia przez podan� �cie�k�
	/// </summary>
	/// <param name="path">�cie�ka w postaci wektora liczb</param>
	/// <returns>Liczba ca�kowita reprezentujaca d�ugo�� �cie�ki</returns>
	int getPathCost(std::vector <int> path);

	/// <summary>
	/// Zerowanie (ustawianie na fa�sz) tablicy tabu
	/// </summary>
	void clearTabuArray();

	/// <summary>
	/// Generowanie pocz�tkowej �cie�ki
	/// </summary>
	/// <returns>Losowa �cie�ka z�o�ona z n miast</returns>
	std::vector <int> generateRandomPath();

	long long int read_QPC();
public:
	
	/// </summary>
	/// G��wna metoda inicjuj�ca wyszukiwanie i wy�wietlaj�ca najlepsze znalezione rozwi�zania
	/// <param name="graph">Graf miast</param>
	/// <param name="timeToStop">Kryterium czasowe ko�ca wyszukiwania podane w sekundach</param>
	/// <param name="diversification">Dywersyfikacja (true-w��czona) </param>
	void search(Graph* graph, int timeToStop, bool diversification);
};

