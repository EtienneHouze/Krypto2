#include "Modulator.h"
#include <iostream>



Modulator::Modulator()
{
}

Modulator::Modulator(BigInt m) {
	mod = m;
	multiples = std::vector<BigInt>(1);
	multiples[0] = m;
	powersOfTwo = std::vector<BigInt>(1);
	powersOfTwo[0] = BigInt(1);
}


BigInt Modulator::multiplication(BigInt a, BigInt b)
{
	auto list = b.getBinary();
	BigInt result = BigInt();
	BigInt temp = a;
	while (!list.empty()) {
		if (list.back())
			result = plus(result, temp);
		temp = temp << 1;
		temp = plus(temp, BigInt());
		list.pop_back();
	}
	return result;
}

BigInt Modulator::plus(BigInt a, BigInt b)
{
	BigInt result = a + b;
	int biggestPower = multiples.size()-1;
	while (multiples[biggestPower] < result) {
		multiples.push_back(multiples[biggestPower] << 1);
		biggestPower++;
	}
	while (biggestPower > -1) {
		if (multiples[biggestPower] < result)
			result = result - multiples[biggestPower];
		biggestPower--;
	}
	return result;
}


BigInt Modulator::exponentiation(BigInt a, BigInt b)
{
	auto list = b.getBinary();
	BigInt result = BigInt(1);
	BigInt temp = a;
	while (!list.empty()) {
		if (list.back()) {
			result = multiplication(result, temp);
		}
		temp = multiplication(temp, temp);
	}
	return result;
}

Modulator::~Modulator()
{
}
