#include <string>
#include <algorithm>
#include <sstream>

#include "BigInt.h"




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

BigInt::BigInt()
{
	binary = std::list<bool>();
	binary.push_back(0);
	decimal = std::vector<unsigned char>(1);
	decimal[0] = 0;
}


void BigInt::updateBinary()
{
	binary = std::list<bool>();
	std::vector<unsigned char> powerOfTwo = { 1 };
	std::vector<std::vector<unsigned char>> powers = std::vector<std::vector<unsigned char>>();
	std::vector<unsigned char> dec = this->decimal;
	while (isGreaterDec(dec, powerOfTwo)) {
		powers.push_back(powerOfTwo);
		powerOfTwo = plusDec(powerOfTwo, powerOfTwo);
	}
	for (int i = powers.size() - 1; i > -1; i--) {
		if (isGreaterDec(dec, powers[i])) {
			binary.push_back(true);
			dec = minusDec(dec, powers[i]);
		}
		else
			binary.push_back(false);
	}

}

void BigInt::updateDecimal()
{

}


BigInt::BigInt(std::string str)
{
	auto decInvert = std::vector<unsigned char>();
	char buffer;
	std::stringstream stream(str);
	while (stream >> buffer) {
		decInvert.push_back(buffer - '0');
	}
	decimal = std::vector<unsigned char>(decInvert.size());
	for (int j = 0; j < decInvert.size(); j++)
		decimal[decimal.size() - 1 - j] = decInvert[j];
	updateBinary();
}

BigInt::BigInt(int i)
{
	std::vector<unsigned char> decInvert = std::vector<unsigned char>();
	while (i > 0) {
		decInvert.push_back((unsigned char)(i % 10));
		i = i / 10;
	}
	decimal = std::vector<unsigned char>(decInvert.size());
	for (int j = 0; j < decInvert.size(); j++)
		decimal[j] = decInvert[j];
	updateBinary();

}

BigInt BigInt::operator+(const BigInt & other) const
{
	BigInt result = BigInt();
	result.binary = std::list<bool>();
	bool mem = false;
	auto thisBin = this->binary;
	auto otherBin = other.binary;
	while ((!thisBin.empty()) && (!otherBin.empty())) {
		result.binary.push_front(
			(thisBin.back() && (!otherBin.back()) && (!mem))
			|| (!(thisBin.back()) && otherBin.back() && (!mem))
			|| ((!thisBin.back()) && (!otherBin.back()) && mem)
			|| (thisBin.back() && otherBin.back() && mem)
		);
		mem = (
			(thisBin.back() && otherBin.back())
			|| (thisBin.back() && mem)
			|| (otherBin.back() && mem)
			);
		thisBin.pop_back();
		otherBin.pop_back();
	}
	while (!thisBin.empty()) {
		result.binary.push_front(
			(thisBin.back() && (!mem))
			|| ((!thisBin.back()) && mem)
		);
		mem = mem && thisBin.back();
		thisBin.pop_back();
	}
	while (!otherBin.empty()) {
		result.binary.push_front(
			(otherBin.back() && (!mem))
			|| ((!otherBin.back()) && mem)
		);
		mem = mem && otherBin.back();
		otherBin.pop_back();
	}
	if (mem)
		result.binary.push_front(true);
	return result;
}

BigInt BigInt::operator<<(const int i) const
{
	BigInt result = *this;
	for (int j = 0; j < i; j++) {
		result.binary.push_back(false);
	}
	return result;
}

BigInt BigInt::operator>>(const int i) const
{
	BigInt result = *this;
	for (int j = 0; j < i; j++) {
		if (!result.binary.empty()) {
			result.binary.pop_back();
		}
	}
	if (result.binary.empty())
		result.binary.push_back(false);
	return result;
}

BigInt BigInt::operator*(const BigInt & other) const
{
	BigInt result = BigInt(0);
	BigInt temp = *this;
	auto list = other.binary;
	while (!list.empty()) {
		if (list.back())
			result = result + temp;
		temp = temp << 1;
		list.pop_back();
	}
	return result;
}

BigInt BigInt::operator-(const BigInt & other) const
{
	BigInt result = BigInt();
	result.binary = std::list<bool>();
	auto thisBin = this->binary;
	auto otherBin = other.binary;
	bool mem = false;
	while ((!thisBin.empty()) && (!otherBin.empty())) {
		result.binary.push_front(
			(thisBin.back() && otherBin.back() && mem)
			|| ((!thisBin.back()) && otherBin.back() && (!mem))
			|| ((!thisBin.back()) && (!otherBin.back()) && mem)
			|| (thisBin.back() && (!otherBin.back()) && (!mem))
		);
		mem = (thisBin.back() && otherBin.back() && mem)
			|| ((!thisBin.back()) && (otherBin.back() || mem));
		thisBin.pop_back();
		otherBin.pop_back();
	}
	while (!thisBin.empty()) {
		result.binary.push_front(
			((!thisBin.back()) && mem)
			|| (thisBin.back() && !mem)
		);
		mem = (!thisBin.back()) && mem;
		thisBin.pop_back();
	}
	while (!(result.binary.front()) && (!result.binary.empty()))
		result.binary.pop_front();
	return result;
}

BigInt& BigInt::operator=(const BigInt & other)
{
	this->binary = other.binary;
	this->decimal = other.decimal;
	return *this;
}

bool BigInt::operator<(const BigInt & other) const
{
	if (this->binary.size() < other.binary.size())
		return true;
	if (this->binary.size() > other.binary.size())
		return false;
	std::list<bool> thisBin = this->binary;
	std::list<bool> otherBin = other.binary;
	while (!thisBin.empty()) {
		if (thisBin.front() == otherBin.front()) {
			thisBin.pop_front();
			otherBin.pop_front();
		}
		else {
			return (otherBin.front());
		}
	}
	return false; // This means both are equal.
}

bool BigInt::operator==(const BigInt & other) const
{
	return ((!(*this < other)) && (!(other < *this))); // equallity means no one is bigger than the other.
}

std::string BigInt::toString()
{
	return std::string();
}
