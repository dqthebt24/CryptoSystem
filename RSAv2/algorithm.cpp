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

BigInt Algorithm::MulMod(const BigInt& x, const BigInt& y, const BigInt& n)

{
    BigInt res("0");
    BigInt rezo("0");

    if (x == rezo || y == rezo || n == rezo) {
        return res;
    }

    BigInt znX = x % n;
    BigInt znY = y % n;
    string strZnY = znY.getDigits();

    int lenY = (int)strZnY.length();
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
