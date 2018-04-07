#pragma once
#include <vector>
#include <string>

class BigInt
{
private:
	// decimal representation of the number, with [0] being the least significant digit
	std::vector<bool> binary;
	//	binary representation of the number, with [0] being the least significant bit
	std::vector<unsigned char> decimal;

	// The following are helper internal methods.

	// Substraction method. We presume here that a > b;
	std::vector<unsigned char> minusDec(std::vector<unsigned char> a, std::vector<unsigned char> b);
	// Decimal addition method
	std::vector<unsigned char> plusDec(std::vector<unsigned char> a, std::vector<unsigned char> b);
	// Checks which decimal is bigger
	bool isGreaterDec(const std::vector<unsigned char> a,const std::vector<unsigned char> b);

	std::vector<bool> plusBin(std::vector<bool>a, std::vector<bool>b);

	std::vector<bool> minusBin(std::vector<bool>a, std::vector<bool>b);

	std::vector<unsigned char> binToDec(std::vector<bool>a);

	std::vector<bool> decToBin(std::vector<unsigned char>a);

public:
	BigInt() {
		binary = std::vector<bool>();
		decimal = std::vector<unsigned char>();
	}

	BigInt(std::string str);

	void parseString(std::string);

	std::string toStringDec();

	BigInt operator+(BigInt& other);

	BigInt operator-(BigInt other);

	BigInt operator*(const BigInt& other)const;

	BigInt operator%(BigInt other);

	bool operator<( BigInt other);

	BigInt& operator=(BigInt other);

	bool operator==(BigInt other);

	static BigInt modexp(BigInt a, BigInt b, BigInt n);

	~BigInt();
};

