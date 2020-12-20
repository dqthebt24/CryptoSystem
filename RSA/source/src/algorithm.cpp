#include <algorithm>
#include <cstring>
#include <string>
#include <time.h>
#include "define.h"
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
    if (!(n > ZERO)) {
        return ZERO;
    } else if (!(p > ZERO)) {
        return ONE % n;
    } else if (p == ONE) {
        return x % n;
    } else if (x == ZERO) {
        return ZERO;
    }

    BigInt znX = x, res("1");
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

BigInt Algorithm::Div(const BigInt& x, const BigInt& y)
{
    
    int lenX = (int)x.getLen();
    int lenY = (int)y.getLen();
    int diffLen = lenX - lenY;

    if (diffLen == 0) {
        return x >= y ? BigInt("1") : BigInt("0");
    } else if (diffLen < 0) {
        return BigInt("0");
    } else {

        char* resDigits = new char[diffLen + 2];
        resDigits[diffLen + 1] = '\0';

        BigInt zero("0");

        auto appendBit = [](char* oldChars, char bit) -> char* {
            if (oldChars != nullptr) {
                char* newChars = new char[strlen(oldChars) + 2];
                memcpy(newChars, oldChars, strlen(oldChars));
                newChars[strlen(oldChars)] = bit;
                newChars[strlen(oldChars) + 1] = '\0';
                delete[] oldChars;
                return newChars;
            } else {
                oldChars = new char[2];
                oldChars[0] = bit;
                oldChars[1] = '\0';
                return oldChars;
            }
        };

        auto reAssignBit = [&](BigInt& number) -> char* {
            char* chars;
            if (number == zero) {
                chars = nullptr;
            } else {
                chars = new char[number.getLen() + 1];
                memcpy(chars, number.getDigits(), number.getLen());
                chars[number.getLen()] = '\0';
            }
            return chars;
        };

        char* tmpDigits = new char[lenY];
        memcpy(tmpDigits, x.getDigits(), lenY - 1);
        tmpDigits[lenY - 1] = '\0';

        for (int i = lenY - 1; i < lenX; i++) {
            tmpDigits = appendBit(tmpDigits, x.getDigits()[i]);
            BigInt num = BigInt(tmpDigits);
            num.format();
            if (num >= y) {
                resDigits[diffLen - lenX + i + 1] = '1';
                BigInt sub = num - y;

                delete[] tmpDigits;

                tmpDigits = reAssignBit(sub);

            } else {
                resDigits[diffLen - lenX + i + 1] = '0';
            }
        }

        BigInt res(resDigits);

        if (tmpDigits != nullptr) {
            delete[] tmpDigits;
        }

        delete[] resDigits;
        res.format();
        return res;
    }
}

//BigInt Algorithm::GetEInverse(const BigInt& e, const BigInt& phi)
//{
//    BigInt k("1"), one("1");
//    while (!(k > phi)) {
//        k = k + 1;
//    }
//}

BigInt Algorithm::GetEInverse(const BigInt& e, const BigInt& phi)
{
    BigInt mod = phi % e;
    BigInt  k("0"), total("1"), zero("0"), one("1");

    while (!(total == zero)) {
        k = k + one;
        total = (total + mod) % e;
    }
    return Div(Mul(k, phi) + one, e);
}

/*BigInt Algorithm::GetEInverse(const BigInt& e, const BigInt& phi)
{
    BigInt phiTwoComplement = phi.getTwoComplement();
    BigInt u = phi, v = e, A("1"), B("0"), C("0"), D("1"), zero("0");

    auto isEven = [](BigInt* num) -> bool {
        return num->getDigits()[(int)num->getLen() - 1] == '0';
    };
    cout << "x:" << phi.getDigits()<<"; y:"<<e.getDigits() << endl;
    while (u > zero) {
        cout << "u: " << u.getDigits() << endl;
        cout << "WHILE 1" << endl;
        while (isEven(&u)) {// while phi even
            u = u >> 1;
            cout << "   u: " << u.getDigits() << endl;
            cout << "   A: " << A.getDigits() << "; B: " << B.getDigits() << endl;
            if (isEven(&A) && isEven(&B)) {
                cout << "     do 1\n";
                A = A >> 1;
                B = B >> 1;
            } else {
                cout << "     do 2\n";
                A = ((A + e) >> 1);
                B = (B + phiTwoComplement) >> 1;
            }
        }
        cout << "WHILE 2" << endl;

        while (isEven(&v)) {// while v even
            v = v >> 1;
            if (isEven(&C) && isEven(&D)) {
                C = C >> 1;
                D = D >> 1;
            } else {
                C = ((C + e) >> 1);
                D = ((D + phiTwoComplement) >> 1);
            }
        }

        if (u >= v) {
            u = u - v;
            A = A - C;
            B = B - D;
        } else {
            v = v - u;
            C = C - A;
            D = D - B;
        }
    }

    return D;
}*/
