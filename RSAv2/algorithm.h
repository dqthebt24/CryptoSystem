#pragma once
#include "bigint.h"
class Algorithm {
private:
	static Algorithm* mInstance;

public:
	static Algorithm* GetInstance();
	char* GenBinaryString(int length);
	BigInt MulMod(const BigInt& x, const BigInt& y, const BigInt& n);
};

