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

	//czas rozpoczêcia
	long long int startTime;

	long long int frequency;

	//tablica tabu
	bool** tabuArray;

	/// <summary>
	/// Metoda wyœwietlaj¹ca œcie¿kê
	/// </summary>
	/// <param name="path">Œcie¿ka do wyœwietlenia</param>
	void printPath(std::vector<int> path);

	/// <summary>
	/// Metoda zamieniaj¹ca 2 losowe miasta kolejnoœci¹ (je¿eli ta zmiana nie znajduje siê w tablicy tabu)
	/// </summary>
	/// <param name="path">Œcie¿ka w której ma zostaæ przeprowadzona zamiana</param>
	void swapTwoRandomCities(std::vector<int>* path);



	/// <summary>
	/// Metoda zamieniaj¹ca 2 losowe miasta kolejnoœci¹ (je¿eli ta zmiana nie znajduje siê w tablicy tabu).
	/// Metoda wyszukuje najelsze rozwi¹zania spoœród próby o podanej wielkoœci
	/// </summary>
	/// <param name="path">Œcie¿ka w której ma zajœæ zmiana</param>
	/// <param name="minSearchLength">Minimalna d³ugoœæ szukania(ilosæ œcie¿ek)</param>
	/// <param name="maxSearchLength">Maksymalna d³ugoœæ szukania(ilosæ œcie¿ek)</param>
	/// <param name="plusLength">D³ugoœæ szukania po znalezieniu elementu lepszego od aspiracji</param>
	/// <param name="aspiration">Wartoœæ któr¹ chcemy polepszyæ</param>
	void swapTwoBestRandomCities(std::vector<int>* path, int minSearchLength, int maxSearchLength, int plusLength, int aspiration);

	/// <summary>
	/// Generowanie pocz¹tkowej œcie¿ki na podstawie kolejnych najni¿szych wartoœci
	/// </summary>
	/// <returns>Wygenerowana œcie¿ka</returns>
	std::vector<int> generateInitialPath();

	/// <summary>
	/// Wyliczanie kosztu przejœcia przez podan¹ œcie¿kê
	/// </summary>
	/// <param name="path">Œcie¿ka w postaci wektora liczb</param>
	/// <returns>Liczba ca³kowita reprezentujaca d³ugoœæ œcie¿ki</returns>
	int getPathCost(std::vector <int> path);

	/// <summary>
	/// Zerowanie (ustawianie na fa³sz) tablicy tabu
	/// </summary>
	void clearTabuArray();

	/// <summary>
	/// Generowanie pocz¹tkowej œcie¿ki
	/// </summary>
	/// <returns>Losowa œcie¿ka z³o¿ona z n miast</returns>
	std::vector <int> generateRandomPath();

	long long int read_QPC();
public:
	
	/// </summary>
	/// G³ówna metoda inicjuj¹ca wyszukiwanie i wyœwietlaj¹ca najlepsze znalezione rozwi¹zania
	/// <param name="graph">Graf miast</param>
	/// <param name="timeToStop">Kryterium czasowe koñca wyszukiwania podane w sekundach</param>
	/// <param name="diversification">Dywersyfikacja (true-w³¹czona) </param>
	void search(Graph* graph, int timeToStop, bool diversification);
};

