#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "BigInt.h"
#include "Modulator.h"

std::vector<bool> toBitArray(int a) {
	std::vector<bool> ret = std::vector<bool>(8*sizeof(a));
	for (unsigned char c = 0; c < ret.size(); c++) {
		ret[c] = a % 2 == 1;
		a = a / 2;
	}
	return ret;
}

int main(int argc, char** argv) {
	BigInt test = BigInt("5");
	BigInt test2 = BigInt("117");
	BigInt test3 = BigInt("19");
	BigInt result = test * test2;
	Modulator modulo = Modulator(test3);
	result = modulo.multiplication(test, test2);
	//result = result << 1;
	return 0;
}