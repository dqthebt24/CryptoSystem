#pragma once
#include <cstdint>

using namespace std;

class BigInt {
public:
	char* mDigits;
	size_t len;

public:
	BigInt();
	BigInt(const int numDigits);
	~BigInt();

	size_t getLen() { return len; }
	string getDigits() { return string(mDigits); }

	BigInt operator+(const BigInt n);
	BigInt operator=(BigInt n);
};

