#pragma once
#include <fstream>
#include "Graph.h"
#include <vector>



class File {
private:

	std::vector <int> listOfNumbers;

	/// <summary>
	/// Odczytanie i zapisanie w liœcie () wszystkich numerów w odczytanej lini
	/// </summary>
	/// <param name="file"></param>
	void getAllNumbers(std::ifstream& file);

public:

	/// <summary>
	/// Wczytanie grafu (w post. macierzowej) z pliku wed³ug za³o¿eñ projektowych
	/// </summary>
	void loadGraphFromFile(Graph* gm, std::string fileName);

};

