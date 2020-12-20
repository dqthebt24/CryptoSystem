#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <chrono>
#include "bigint.h"
#include "algorithm.h"

using namespace std;
void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < time_end) {
    }
}

void main_basic()
{
    int bits = 1024;
    std::chrono::steady_clock::time_point begin, end;
    begin = std::chrono::steady_clock::now();
    BigInt a(bits);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;
    sleepcp(1000);
    begin = std::chrono::steady_clock::now();
    BigInt b(bits);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;
    cout << "A= " << a.getDigits() << endl;
    cout << "B= " << b.getDigits() << endl;

    begin = std::chrono::steady_clock::now();
    BigInt c = a + b;
    end = std::chrono::steady_clock::now();
    cout << "C= " << c.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    bool res = a >= b;
    end = std::chrono::steady_clock::now();

    cout << "Compare:" << (a > b) << ";" << (b > a) << ";" << (a >= b) << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    if (!res) {
        return;
    }

    // Test subtraction
    begin = std::chrono::steady_clock::now();
    BigInt d = a - b;
    end = std::chrono::steady_clock::now();
    cout << "D: " << d.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt e = a % b;
    end = std::chrono::steady_clock::now();
    cout << "E: " << e.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;
}

void main_algorithm()
{
    int bits = 1024;
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();

    BigInt a(bits);
    sleepcp(1000);
    BigInt b(512);
    sleepcp(1000);
    BigInt c(512);

    cout << "A= " << a.getDigits() << endl;
    cout << "B= " << b.getDigits() << endl;
    cout << "C= " << c.getDigits() << endl;

    begin = std::chrono::steady_clock::now();
    BigInt sum = a + b;
    end = std::chrono::steady_clock::now();
    cout << "Sum= " << sum.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt mul = algorithm->Mul(a, b);
    end = std::chrono::steady_clock::now();
    cout << "Mul= " << mul.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt mulMod = algorithm->MulMod(a, b, c);
    end = std::chrono::steady_clock::now();
    cout << "MulMod= " << mulMod.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt powMod = algorithm->PowMod(a, b, c);
    end = std::chrono::steady_clock::now();
    cout << "PowMod= " << powMod.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt div = algorithm->Div(a, b);
    end = std::chrono::steady_clock::now();
    cout << "Div= " << div.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;
}

BigInt genPrime(int bits)
{
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();
    vector<BigInt> bases{ BigInt(5), BigInt(7) };
    BigInt six("110");
    BigInt one("1");
    BigInt two("10");
    BigInt tmp(bits - 3);
    BigInt prime;
    bool found = false;

    begin = std::chrono::steady_clock::now();
    while (!found) {
        prime = algorithm->Mul(six, tmp) + one;
        BigInt primeMinusOne = prime - one;

        found = true;
        for (int i = 0; i < (int)bases.size(); i++) {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            BigInt res = algorithm->PowMod(bases[i], primeMinusOne, prime);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "   Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[�s]" << std::endl;

            cout << "   RES: " << res.getDigits() << endl;
            if (!(res == one)) {
                found = false;
                break;
            }
        }

        if (!found) {
            tmp += two;
        }
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    cout << "Prime is: " << prime.getDigits() << endl;
    return prime;
}

void main_rsa()
{
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();

    int bits = 128;
    BigInt p, q, n, phi, one("1"), e("10000000000000001"); // e = 65537
    BigInt m(100);

    p = genPrime(bits);
    q = genPrime(bits);

    n = algorithm->Mul(p, q);

    cout << "P = " << p.getDigits() << endl;
    cout << "Q = " << q.getDigits() << endl;
    cout << "N = " << n.getDigits() << endl;

    phi = algorithm->Mul(p - one, q - one);

    cout << "Phi = " << phi.getDigits() << endl;

    begin = std::chrono::steady_clock::now();
    BigInt d = algorithm->GetEInverse(e, phi);
    end = std::chrono::steady_clock::now();

    cout << "d = " << d.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    cout << "M_org = " << m.getDigits() << endl;
    begin = std::chrono::steady_clock::now();
    BigInt m_enc = algorithm->PowMod(m, e, n);
    end = std::chrono::steady_clock::now();
    cout << "M_enc = " << m_enc.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt m_dec = algorithm->PowMod(m_enc, d, n);
    end = std::chrono::steady_clock::now();
    cout << "M_dec = " << m_dec.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}

void main_inverse()
{
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();

    BigInt e("10000000000000001"), phi(512);

    cout << "phi = " << phi.getDigits() << endl;

    begin = std::chrono::steady_clock::now();
    BigInt d = algorithm->GetEInverse(e, phi);
    end = std::chrono::steady_clock::now();


    cout << "d = " << d.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    /* Test Div
    BigInt x(20);
    sleepcp(1000);
    BigInt y("10000000000000001"), r;

    begin = std::chrono::steady_clock::now();
    r = algorithm->Div(x, y);
    cout << "x = " << x.getDigits() << endl;
    cout << "y = " << y.getDigits() << endl;
    end = std::chrono::steady_clock::now();
    cout << "r = " << r.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;*/
}
int main()
{
    main_algorithm();
    //main_basic();
    //main_rsa();
    //main_inverse();
    return 1;
}