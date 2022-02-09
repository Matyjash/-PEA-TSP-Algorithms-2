#include "Random.h"
#include <random>

int Random::generateRandomNumber(int lowerBound, int upperBound) {
	std::random_device randomDevice;
	std::mt19937 rng(randomDevice());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lowerBound, upperBound - 1);

	int randomNumber = dist(rng);
	return randomNumber;
}