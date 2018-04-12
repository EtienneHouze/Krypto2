#pragma once
#include "BigInt.h"
#include <vector>

class Modulator
{
private:
	BigInt mod;
	std::vector<BigInt> multiples;
	std::vector<BigInt> powersOfTwo;

public:
	Modulator();

	Modulator(BigInt m);

	BigInt multiplication(BigInt a, BigInt b);

	BigInt plus(BigInt a, BigInt b);

	BigInt exponentiation(BigInt a, BigInt b);

	~Modulator();
};

