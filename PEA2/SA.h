#pragma once
#include <vector>
#include "Graph.h"
#include "Random.h"
class SA
{

private:
	//graf miast
	Graph* graph;

	//czas rozpocz�cia
	long long int startTime;

	long long int frequency;

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
	/// Metoda sprawdzaj�ca czy podany czas ju� up�yn��
	/// </summary>
	/// <returns>True je�eli czas up�yn��, False je�eli nie</returns>
	bool isTimeUp();

	/// <summary>
	/// Metoda obliczaj�ca prawdopodobie�stwo przyjecia nowego rozwi�zania
	/// </summary>
	/// <param name="cost">Aktualny koszt przejscia przez sciezke</param>
	/// <param name="newCost">Nowy, wyliczony koszt przejscia przez now� �cie�k�</param>
	/// <param name="temperature">Aktualna temperatura</param>
	/// <returns></returns>
	double getProbabillity(int cost, int newCost, double temperature);

	/// <summary>
	/// Metoda zamieniaj�ca 2 losowe miasta kolejno�ci�
	/// </summary>
	/// <param name="path">�cie�ka w kt�rej ma zosta� przeprowadzona zamiana</param>
	void swapTwoRandomCities(std::vector<int>* path);

	long long int read_QPC();

	/// <summary>
	/// Generowanie pocz�tkowej �cie�ki
	/// </summary>
	/// <returns>Losowa �cie�ka z�o�ona z n miast</returns>
	std::vector <int> generateRandomPath();

	/// <summary>
	/// Ch�odzenie za pomoc� parametru alfa
	/// </summary>
	/// <param name="currentTemperature"></param>
	/// <param name="alpha"></param>
	/// <returns></returns>
	float updateTemperature(float currentTemperature, float alpha);

public:
	/// <summary>
	/// Liczenie optymalnej �cie�ki metod� symulowanego wy�arzania
	/// </summary>
	/// <param name="graph">Graf miast</param>
	/// <param name="timeToStop">Czas do zako�czenia symluacji</param>
	void simulateAnneling(Graph* graph, int timeToStop);
};

