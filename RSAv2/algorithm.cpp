#include <algorithm>
#include <cstring>
#include <string>
#include <time.h>
#include "algorithm.h"

#include <iostream>

using namespace std;

Algorithm* Algorithm::mInstance = nullptr;

Algorithm* Algorithm::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new Algorithm();
	}
	return mInstance;
}

char* Algorithm::GenBinaryString(int length)
{
    srand((unsigned int)time(nullptr));
    auto randchar = []() -> char {
        const char charset[] = "01";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };

    string str(length, 0);
    generate_n(str.begin(), length, randchar);

    char* cstr = new char[str.length() + 1];
    memcpy(cstr, str.c_str(), length);
    cstr[length] = '\0';
    return cstr;
}

BigInt Algorithm::Mul(const BigInt& x, const BigInt& y)
{
    BigInt res("0");
    BigInt zero("0");

    if (x == zero || y == zero) {
        return zero;
    }

    BigInt X = x;
    BigInt Y = y;
    char* strY = Y.getDigits();

    int lenY = (int)strlen(strY);
    int i = lenY - 1;

    if (strY[i] == '1') {
        res = X;
    }

    i--;
    for (; i >= 0; i--) {
        X = X << 1;

        if (strY[i] == '1') {
            res += X;
        }
    }

    return res;
}

BigInt Algorithm::MulMod(const BigInt& x, const BigInt& y, const BigInt& n)

{
    BigInt res("0");
    BigInt zero("0");

    if (!(x > zero) || !(y > zero) || !(n > zero)) {
        return res;
    }

    BigInt znX = x % n;
    BigInt znY = y % n;
    char* strZnY = znY.getDigits();

    int lenY = (int)strlen(strZnY);
    int i = lenY - 1;

    if (strZnY[i] == '1') {
        res = znX;
    }

    i--;
    for (; i >= 0; i--) {
        znX = znX << 1;
        
        if (strZnY[i] == '1') {
            res+=znX;
        }
    }

    return res % n;
}

BigInt Algorithm::PowMod(const BigInt& x, const BigInt& p, const BigInt& n)
{
    BigInt res("1");
    BigInt zero("0");

    if (!(n > zero) || !(x > zero) || !(p > zero)) {
        return zero;
    }

    if (p == zero) {
        return res;
    }

    BigInt znX = x;
    char* strP = p.getDigits();
    int lenP = (int)strlen(strP);

    if (strP[lenP - 1] == '1') {
        res = znX;
    }

    for (int i = 2; i <= lenP; i++) {
        znX = MulMod(znX, znX, n);
        if (strP[lenP - i] == '1') {
            res = MulMod(res, znX, n);
        }
    }

    return res;
}
