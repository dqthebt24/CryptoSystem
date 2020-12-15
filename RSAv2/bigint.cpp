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
		printf("THIS0000: %x;;;%x\n",this, this->mDigits);
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
		printf("DEL: %x\n", mDigits);
		delete[] mDigits;
		mDigits = nullptr;
	}
}

BigInt BigInt::operator+(const BigInt n)
{
	bool isRemembered = false;
	int len = (int)strlen(mDigits);
	int lenN = (int)strlen(n.mDigits);
	size_t lenMax = MAX(len, lenN);
	int idx = lenMax - 1;

	len--;
	lenN--;
	char* res = new char[lenMax + 1];
	char c = '0';
	while (len >= 0 || lenN >= 0) {
		char a = len >= 0 ? mDigits[len] : '0';
		char b = lenN >= 0 ? n.mDigits[lenN] : '0';
		res[idx] = ((a^b)^c);
		c = (a & b) | (a & c) | (b & c);
		idx--;
		len--;
		lenN--;
	}

	res[lenMax] = '\0';
	if (c == '1') {
		char* tmp = this->mDigits;
		this->mDigits = new char[lenMax + 2];
		memcpy(this->mDigits + 1, res, lenMax);
		this->mDigits[lenMax + 1] = '\0';
		this->mDigits[0] = '1';
		//cout << "RES1:" << this->mDigits << endl;
		delete[] tmp;
		delete[] res;
	} else {
		char* tmp = this->mDigits;
		this->mDigits = new char[lenMax + 1];
		memcpy(this->mDigits, res, lenMax);
		//cout << "RES2:" << this->mDigits << endl;
		delete[] tmp;
		delete[] res;
	}
	printf("THIS: %x;;%x\n", this, this->mDigits);
	return *this;
}

BigInt BigInt::operator=(BigInt n)
{
	cout << "NEWWWWWWWWWWW\n";
	return BigInt();
}
