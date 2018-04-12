#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "BigInt.h"
#include "Modulator.h"


int main(int argc, char** argv) {
	/*BigInt test = BigInt("450");
	BigInt test2 = BigInt("768");
	BigInt test3 = BigInt("517");
	BigInt result = test * test2;
	Modulator modulo = Modulator(test3);
	result = modulo.exponentiation(test, test2);
	result.updateDecimal();*/
	
	std::string line;
	std::cout << "hello" << std::endl;
	while (std::getline(std::cin, line)) {
		std::stringstream stream(line);
		std::string a, b, c;
		stream >> a >> b >> c;
		BigInt A = BigInt(a);
		BigInt B = BigInt(b);
		BigInt C = BigInt(c);
		Modulator mod = Modulator(c);
		BigInt result = mod.exponentiation(A, B);
		result.updateDecimal();
		std::cout << result.toString() << std::endl;
	}
	return 0;
}