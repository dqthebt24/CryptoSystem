#pragma once
#include "bigint.h"
class Algorithm {
private:
	static Algorithm* mInstance;

public:
	static Algorithm* GetInstance();
	char* GenBinaryString(int length);
	BigInt Mul(const BigInt& x, const BigInt& y);
	BigInt MulMod(const BigInt& x, const BigInt& y, const BigInt& n);
	BigInt PowMod(const BigInt& x, const BigInt& p, const BigInt& n);
};

