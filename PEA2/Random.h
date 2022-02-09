#pragma once
class Random
{
public:
	/// <summary>
	/// Losowanie liczby ca³kowitej z podanego przedzia³u
	/// </summary>
	/// <param name="lowerBound">Dolna granica</param>
	/// <param name="upperBound">Górna granica</param>
	/// <returns>Wylosowana liczba</returns>
	static int  generateRandomNumber(int lowerBound, int upperBound);

};

