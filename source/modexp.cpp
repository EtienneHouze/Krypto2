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

//std::vector<int> power2decomp(unsigned long long a) {
//	std::vector<unsigned long long> ret = std::vector<unsigned long long>(8*sizeof(a),0);
//	auto bits = toBitArray(a);
//	unsigned long long pow = 1;
//	for (unsigned char c = 0; c < ret.size();c++) {
//		if (bits[c]) {
//			ret[c] = pow;
//		}
//		pow *= 2;
//	}
//	return ret;
//	
//}
//
//int modexpPower2(unsigned long long a, unsigned long long b, unsigned long long n) {
//	int r = a;
//	while (b > 1) {
//		r = (r*r) % n;
//		b /= 2;
//	}
//	return r;
//}

//int modexp(unsigned long long a, unsigned long long b, unsigned long long n) {
//	int r = 1;
//	if (b == 0)
//		return 1;
//	auto powers = power2decomp(b);
//	for (unsigned char c = 0; c < powers.size(); c++) {
//		if (powers[c] != 0)
//			r = (r * modexpPower2(a, powers[c], n)) % n;
//		
//	}
//	return r;
//}

int main(int argc, char** argv) {
	std::string line;
	/*std::string text = "3 3 5 \n 0 1 5 \n1 5 7";
	std::istringstream inputFile(text);*/
	while (std::getline(std::cin, line)) {
		std::stringstream ss(line);
		std::string strA, strB, strN;
		ss >> strA >> strB >> strN;
		BigInt a = BigInt(strA);
		BigInt b = BigInt(strB);
		BigInt n = BigInt(strN);
		BigInt res = BigInt::modexp(a, b, n);
		std::cout << res.toStringDec() << std::endl;
	}
	/*std::string str = "5";
	std::string strBis = "117";
	std::string strTer = "19";
	BigInt text = BigInt();
	text.parseString(str);
	BigInt test2 = BigInt();
	test2.parseString(strBis);
	BigInt test3 = BigInt();
	test3.parseString(strTer);
	BigInt test4 = BigInt::modexp(text, test2, test3);
	std::cout << test4.toStringDec();*/
	return 0;
}