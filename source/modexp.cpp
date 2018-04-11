#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "BigInt.h"

std::vector<bool> toBitArray(int a) {
	std::vector<bool> ret = std::vector<bool>(8*sizeof(a));
	for (unsigned char c = 0; c < ret.size(); c++) {
		ret[c] = a % 2 == 1;
		a = a / 2;
	}
	return ret;
}

int main(int argc, char** argv) {
	BigInt test = BigInt("415678613855765135249686746521687");
	BigInt test2 = BigInt("12387498765168746516587468546587");
	BigInt result = test * test2;
	//result = result << 1;
	return 0;
}