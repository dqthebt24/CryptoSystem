#include <iostream>
#include "define.h"
#include "algorithm.h"
#include "bigint.h"

BigInt::BigInt(): mDigits(nullptr), len(0)
{
}

BigInt::BigInt(const int numDigits)
{
	if (numDigits > 0) {
		mDigits = Algorithm::GetInstance()->GenBinaryString(numDigits);
		mDigits[0] = '1';
		len = strlen(mDigits);
	}
	else {
		mDigits = nullptr;
		len = 0;
	}
}

BigInt::~BigInt()
{
	cout << "~~~~~~~~~~~~" << endl;
	if (mDigits != nullptr) {
		cout << "Delete!!!!!" << endl;
		len = 0;
		delete mDigits;
		mDigits = nullptr;
	}
}

BigInt BigInt::operator+(const BigInt n)
{
	string strN = n.mDigits;
	bool isRemembered = false;
	size_t len = strlen(mDigits);
	size_t lenN = strlen(n.mDigits);
	size_t lenMax = MAX(len, lenN);
	int idx = lenMax - 1;

	len--;
	lenN--;
	char* res = new char[lenMax + 1];
	char c = '0';
	while (len >= 0 || lenN >= 0) {
		char a = len >= 0 ? mDigits[len] : '0';
		char b = lenN >= 0 ? strN[lenN] : '0';
		res[idx] = ((a^b)^c);
		c = (a & b) | (a & c) | (b & c);
		idx--;
		len--;
		lenN--;
	}

	if (c == '1') {
		res[0] = '1';
		res[lenMax + 1] = '\0';
		delete[] this->mDigits;
		this->mDigits = res;
	} else {
		res[lenMax] = '\0';
		memcpy(this->mDigits, res + 1, lenMax);
		delete[] res;
	}

	return *this;
}
