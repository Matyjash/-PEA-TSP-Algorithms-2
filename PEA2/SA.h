#pragma once
#include <vector>
#include "Graph.h"
#include "Random.h"
class SA
{

private:
	//graf miast
	Graph* graph;

	//czas rozpoczêcia
	long long int startTime;

	long long int frequency;

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
	/// Metoda sprawdzaj¹ca czy podany czas ju¿ up³yn¹³
	/// </summary>
	/// <returns>True je¿eli czas up³yn¹³, False je¿eli nie</returns>
	bool isTimeUp();

	/// <summary>
	/// Metoda obliczaj¹ca prawdopodobieñstwo przyjecia nowego rozwi¹zania
	/// </summary>
	/// <param name="cost">Aktualny koszt przejscia przez sciezke</param>
	/// <param name="newCost">Nowy, wyliczony koszt przejscia przez now¹ œcie¿kê</param>
	/// <param name="temperature">Aktualna temperatura</param>
	/// <returns></returns>
	double getProbabillity(int cost, int newCost, double temperature);

	/// <summary>
	/// Metoda zamieniaj¹ca 2 losowe miasta kolejnoœci¹
	/// </summary>
	/// <param name="path">Œcie¿ka w której ma zostaæ przeprowadzona zamiana</param>
	void swapTwoRandomCities(std::vector<int>* path);

	long long int read_QPC();

	/// <summary>
	/// Generowanie pocz¹tkowej œcie¿ki
	/// </summary>
	/// <returns>Losowa œcie¿ka z³o¿ona z n miast</returns>
	std::vector <int> generateRandomPath();

	/// <summary>
	/// Ch³odzenie za pomoc¹ parametru alfa
	/// </summary>
	/// <param name="currentTemperature"></param>
	/// <param name="alpha"></param>
	/// <returns></returns>
	float updateTemperature(float currentTemperature, float alpha);

public:
	/// <summary>
	/// Liczenie optymalnej œcie¿ki metod¹ symulowanego wy¿arzania
	/// </summary>
	/// <param name="graph">Graf miast</param>
	/// <param name="timeToStop">Czas do zakoñczenia symluacji</param>
	void simulateAnneling(Graph* graph, int timeToStop);
};

