#pragma once
#include <cstdint>
#include <vector>

using namespace std;

class BigInt {
private:
	char* mDigits;
	size_t len;
	vector<BigInt> _split(const BigInt& n, const int width) const;
	void _firstComplement(char* digits);
	void _shiftLeft(const int bits, const bool useFormat = true);
	void _shiftRight(const int bits, const bool useFormat = true);
	void format();
	int _len() {return (int)strlen(mDigits);}

public:
	BigInt();
	BigInt(const int numDigits);
	BigInt(const char* digits);
	BigInt(const BigInt& bigInt);
	~BigInt();

	void setDigits(char* digits) {this->mDigits = digits;}
	void setLen(size_t len) {this->len = len;}

	size_t getLen() { return len; }
	char* getDigits() const { return mDigits; }

	// Calculations
	void operator=(const BigInt& n);
	BigInt operator+(const BigInt n);
	void operator+=(const BigInt& n);
	BigInt operator%(const BigInt& n) const;
	BigInt operator-(const BigInt& n);
	BigInt operator>>(const int bits);
	BigInt operator<<(const int bits);

	// Comparations
	bool operator>(const BigInt& n) const;
	bool operator==(const BigInt& n) const;
	bool operator>=(const BigInt& n) const;
};
