#pragma once
#include <vector>
#include <string>
#include <list>


/*
	A class to represent big positive integers. The operations are done using the binary representation, stored in a list of booleans.
	However, a decimal representation is used to read from integers and print into strings.
*/
class BigInt
{
private:

	std::vector<unsigned char> decimal; // Decimal representation of the number

	std::list<bool> binary; // binary representation of the number. The head of the list is the most important bit.

	void updateBinary(); // Creates the binary from the decimal.

	void updateDecimal(); // Creates the decimal from the binary.

public:
	
	/**

	Substraction of two decimal representations.

	This method requires a > b

	*/
	std::vector<unsigned char> minusDec(std::vector<unsigned char> a, std::vector<unsigned char> b);
	/*

	Addition of two decimal representations.



	*/
	std::vector<unsigned char> plusDec(std::vector<unsigned char> a, std::vector<unsigned char> b);
	/*

	Compares two decimal representations

	*/
	bool isGreaterDec(const std::vector<unsigned char> a, const std::vector<unsigned char> b);

	BigInt();

	BigInt(std::string str);

	BigInt(int i);

	BigInt operator+(const BigInt & other)const;

	//BigInt operator%(const BigInt & other)const;

	BigInt operator<<(const int i)const; // Shift of bits -> result in multiplying by 2^i.

	BigInt operator>>(const int i)const;  // Shift of bits -> results in dividing by 2^i.

	BigInt operator*(const BigInt & other)const;

	BigInt operator-(const BigInt & other)const;

	BigInt& operator=(const BigInt& other);

	bool operator<(const BigInt& other)const;

	bool operator==(const BigInt& other)const;

	std::string toString();

	~BigInt() {};
};

