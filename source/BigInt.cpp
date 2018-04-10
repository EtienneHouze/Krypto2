#include <string>
#include <algorithm>

#include "BigInt.h"



/**
	Substraction of two decimal representations.
	This method requires a > b
*/
std::vector<unsigned char> BigInt::minusDec(std::vector<unsigned char> a, std::vector<unsigned char> b)
{
	bool mem = false;
	std::vector<unsigned char> rep = std::vector<unsigned char>();
	while (a.size() > b.size()) {
		b.push_back(0);
	}
	while (a.size() < b.size()) {
		a.push_back(0);
	}
	for (int i = 0; i < a.size(); i++) {
		unsigned char temp = 10 + a[i] - b[i];
		if (mem) {
			temp -= 1;
			mem = false;
		}
		if (temp < 10) {
			mem = true;
		}
		else {
			temp -= 10;
		}
		rep.push_back(temp);
	}
	return rep;
}


/*
	Addition of two decimal representations.

*/
std::vector<unsigned char> BigInt::plusDec(std::vector<unsigned char> a, std::vector<unsigned char> b)
{
	std::vector<unsigned char> aBis, bBis;
	aBis = a;

	bool mem = false;
	std::vector<unsigned char> rep = std::vector<unsigned char>();
	while (a.size() > b.size()) {
		b.push_back(0);
	}
	while (a.size() < b.size()) {
		a.push_back(0);
	}
	a.push_back(0);
	b.push_back(0);
	for (int i = 0; i < a.size(); i++) {
		unsigned char temp = a[i] + b[i];
		if (mem) {
			temp += 1;
			mem = false;
		}
		if (temp > 9) {
			temp -= 10;
			mem = true;
		}
		else {
			mem = false;
		}
		rep.push_back(temp);
	}
	if (rep[rep.size() - 1] == 0)
		rep.erase(rep.end() - 1);
	return rep;
}

/*
	Compares two decimal representations
*/
bool BigInt::isGreaterDec(const std::vector<unsigned char> a, const std::vector<unsigned char> b) {
	int greatestNonZeroA = a.size() - 1;
	while (greatestNonZeroA > -1) {
		if (a[greatestNonZeroA] == 0)
			greatestNonZeroA--;
		else
			break;
	}
	if (greatestNonZeroA == -1)
		return false;
	int greatestNonZeroB = b.size() - 1;
	while (greatestNonZeroB > -1) {
		if (b[greatestNonZeroB] == 0)
			greatestNonZeroB--;
		else
			break;
	}
	if (greatestNonZeroA > greatestNonZeroB)
		return true;
	if (greatestNonZeroB > greatestNonZeroA)
		return false;
	for (int i = greatestNonZeroA; i > -1; i--) {
		if (a[i] < b[i])
			return false;
		if (b[i] < a[i])
			return true;
	}
	return true;
}

std::vector<bool> BigInt::plusBin(std::vector<bool> a, std::vector<bool> b)
{
	std::vector<bool> ret = std::vector<bool>();
	bool mem = false;
	while (a.size() < b.size()) {
		a.push_back(false);
	}
	while (b.size() < a.size()) {
		b.push_back(false);
	}
	a.push_back(false);
	b.push_back(false);
	for (int i = 0; i < a.size(); i++) {
		bool temp = false;
		temp = ((a[i] && (!b[i]) && !mem) || (!a[i] && b[i] && !mem) || (!a[i] && !b[i] && mem)) || (a[i] && b[i] && mem);
		mem = (a[i] && b[i]) || (mem && a[i]) || (mem && b[i]);
		ret.push_back(temp);
		
	}
	if (!ret[ret.size() - 1])
		ret.erase(ret.end() - 1);
	return ret;
}

std::vector<bool> BigInt::minusBin(std::vector<bool> a, std::vector<bool> b)
{
	std::vector<bool> ret = std::vector<bool>();
	bool mem = false;
	while (b.size() < a.size()) {
		b.push_back(false);
	}
	for (int i = 0; i < a.size(); i++) {
		bool temp = false;
		temp = (a[i] && !b[i] && !mem) || (!a[i] && b[i] && !mem) || (!a[i] && !b[i] && mem) && (a[i] && b[i] && temp);
		mem = (!a[i] && (b[i] || mem)) || (a[i] && b[i] && mem);
		ret.push_back(temp);
	}
	return ret;
}

std::vector<unsigned char> BigInt::binToDec(std::vector<bool> a)
{
	BigInt power = BigInt();
	BigInt ret = BigInt();
	power.binary = std::vector<bool>(1);
	power.decimal = std::vector<unsigned char>(1);
	power.binary[0] = true;
	power.decimal[0] = 1;
	for (int i = 0; i < a.size(); i++) {
		if (a[i]) {
			ret = ret + power;
		}
		power = power + power;
	}
	return ret.decimal;
}

std::vector<bool> BigInt::decToBin(std::vector<unsigned char> a)
{
	std::vector<bool> ret = std::vector<bool>();
	std::vector<std::vector<unsigned char>> powers = std::vector<std::vector<unsigned char>>();
	std::vector<unsigned char> power = std::vector<unsigned char>(1);
	power[0] = 1;
	powers.push_back(power);
	while (isGreaterDec(a, power)) {
		power = plusDec(power, power);
		powers.push_back(power);
	}
	powers.erase(powers.end() - 1);
	std::vector<unsigned char> decCopy = a;
	for (int i = powers.size() - 1; i >= 0; i--) {
		if (isGreaterDec(decCopy, powers[i])) {
			ret.push_back(true);
			decCopy = minusDec(decCopy, powers[i]);
		}
		else
			ret.push_back(false);
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

BigInt::BigInt(std::string str)
{
	this->parseString(str);
}

void BigInt::parseString(std::string str)
{
	decimal = std::vector<unsigned char>(str.size());
	for (int i = str.size() - 1; i >= 0; i--) {
		decimal[decimal.size() - 1 - i] = (unsigned char)str[i] - '0';
	}
	std::vector<std::vector<unsigned char>> powers = std::vector<std::vector<unsigned char>>();
	std::vector<unsigned char> power = std::vector<unsigned char>(1);
	power[0] = 1;
	powers.push_back(power);
	while (isGreaterDec(decimal, power)) {
		power = plusDec(power, power);
		powers.push_back(power);
	}
	powers.erase(powers.end() - 1);
	std::vector<unsigned char> decCopy = decimal;
	for (int i = powers.size() - 1; i >= 0; i--) {
		if (isGreaterDec(decCopy, powers[i])) {
			binary.push_back(true);
			decCopy = minusDec(decCopy, powers[i]);
		}
		else
			binary.push_back(false);
	}
	std::reverse(binary.begin(), binary.end());


}

std::string BigInt::toStringDec()
{
	std::string rep = std::string();
	for (int i = 0; i < decimal.size(); i++) {
		rep.push_back(decimal[decimal.size() - 1 - i]+'0');
	}
	return rep;
}

BigInt BigInt::operator+(BigInt & other)
{
	BigInt ret = BigInt();
	ret.binary = plusBin(binary, other.binary);
	ret.decimal = plusDec(decimal, other.decimal);
	return ret;
}

BigInt BigInt::operator-(BigInt other)
{
	BigInt ret = BigInt();
	ret.decimal = minusDec(decimal, other.decimal);
	ret.binary = minusBin(binary, other.binary);
	return ret;
}

BigInt BigInt::operator*(const BigInt & other) const
{
	BigInt ret = BigInt();
	ret.binary = std::vector<bool>(1, false);
	ret.decimal = std::vector<unsigned char>(1, 0);
	BigInt multiples = *this;
	for (int i = 0; i < other.binary.size(); i++) {
		if (other.binary[i]) {
			ret = ret + multiples;
		}
		multiples = multiples + multiples;
	}
	return ret;
}

BigInt BigInt::operator%(BigInt other)
{
	BigInt ret = BigInt();
	BigInt copy = *this;
	while (other < copy) {
		copy = copy - other;
	}
	return copy;
}

bool BigInt::operator<(BigInt other)
{
	return !isGreaterDec(decimal,other.decimal);
}

BigInt& BigInt::operator=(BigInt other)
{
	decimal = other.decimal;
	binary = other.binary;
	return *this;
}

bool BigInt::operator==(BigInt other)
{
	return (!(*this<other)) && (!(other<*this));
}

BigInt BigInt::modexp(BigInt a, BigInt b, BigInt n)
{
	BigInt ret = BigInt();
	ret.binary = std::vector<bool>(1, true);
	ret.decimal = std::vector<unsigned char>(1, 1);
	/*BigInt power = BigInt();
	power.binary = std::vector<bool>(1, true);
	power.decimal = std::vector<unsigned char>(1, 1);*/
	BigInt power = a;
	for (int i = 0; i < b.binary.size(); i++) {
		if (b.binary[i]) {
			ret = (ret * power) % n;
		}
		power = power * power;
		power = (power)%n;
	}
	while (!(*(ret.binary.end() - 1)) && ret.binary.size() > 1)
		ret.binary.erase(ret.binary.end() - 1);
	while (*(ret.decimal.end() - 1) == 0 && ret.decimal.size() > 1) {
		ret.decimal.erase(ret.decimal.end() - 1);
	}
	return ret;
}

BigInt::~BigInt()
{
}
