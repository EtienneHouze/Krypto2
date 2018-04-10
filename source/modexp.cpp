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
	std::string line;
	std::string strA, strB, strN;
	while (std::getline(std::cin, line)) {
		std::stringstream ss(line);
		ss >> strA >> strB >> strN;
		BigInt a = BigInt(strA);
		BigInt b = BigInt(strB);
		BigInt n = BigInt(strN);
		BigInt res = BigInt::modexp(a, b, n);
		std::cout << res.toStringDec() << std::endl;
	}
	return 0;
}