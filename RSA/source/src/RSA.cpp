#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <chrono>
#include "define.h"
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
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
    sleepcp(1000);
    begin = std::chrono::steady_clock::now();
    BigInt b(bits);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
    cout << "A= " << a.getDigits() << endl;
    cout << "B= " << b.getDigits() << endl;

    begin = std::chrono::steady_clock::now();
    BigInt c = a + b;
    end = std::chrono::steady_clock::now();
    cout << "C= " << c.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    bool res = a >= b;
    end = std::chrono::steady_clock::now();

    cout << "Compare:" << (a > b) << ";" << (b > a) << ";" << (a >= b) << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    if (!res) {
        return;
    }

    // Test subtraction
    begin = std::chrono::steady_clock::now();
    BigInt d = a - b;
    end = std::chrono::steady_clock::now();
    cout << "D: " << d.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt e = a % b;
    end = std::chrono::steady_clock::now();
    cout << "E: " << e.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
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
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt mul = algorithm->Mul(a, b);
    end = std::chrono::steady_clock::now();
    cout << "Mul= " << mul.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt mulMod = algorithm->MulMod(a, b, c);
    end = std::chrono::steady_clock::now();
    cout << "MulMod= " << mulMod.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt powMod = algorithm->PowMod(a, b, c);
    end = std::chrono::steady_clock::now();
    cout << "PowMod= " << powMod.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt div = algorithm->Div(a, b);
    end = std::chrono::steady_clock::now();
    cout << "Div= " << div.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
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
            std::cout << "   Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

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

void main_compare()
{
    const int bits = 1024;
    Algorithm* alg = Algorithm::GetInstance();
    std::chrono::steady_clock::time_point begin, end;
    BigInt a, b, c;

    cout<<"Test Calculation version without boost::multiprecision "<<bits<<" bits!\n";
    

    if (bits == 512) {
        a = BigInt("11101111010010001001011011010000000101011100101000111110101010011111000101000010110111111000110100111111100111010101011100110101110101111011100001011001101110011000101011100110001011110100101101001111001110100010000101001100100101001000001110111000011001100010101111110010110000111011011110111101101010101101001010010000011010001000011110011001000001010110000001100011010001000001101010100011011011111100001111001100111100001100011111100011000111110111101100101101101011111100011011000110010111001011111111001101");
        b = BigInt("10111100110001001001100101001111110000100001100010111100001101011111001111101010101100011010010000100011111100001011110000011000000101000010101111000111110100011001000001010110100001010000111110000010101011111000111001110001111110100001001100011000111001011101010100110110100110010110011110001100110001000101110110011111011101111010001111111110000110111110111001010111111100000100010100101100111100100100011111100111100110000101111100101001101011001000111010101110011100011111000000001011111001000101100111011001");
        c = BigInt("10111100110001001001100101001111110000100001100010111100001101011111001111101010101100011010010000100011111100001011110000011000000101000010101111000111110100011001000001010110100001010000111110000010101011111000111001110001111110100001001100011000111001011101010100110110100110010110011110001100110001000101110110011111011101111010001111111110000110111110111001010111111100000100010100101100111100100100011111100111100100001100011111100011000111110111101100101101101011111100011011000110010111001011111111001101");
    } else {
        a = BigInt("1111101000100001000011101101111100000000110000011010111010110010111110111101100000010101000110001100100111001100001010011010101111100111011110001111010111100001101100101111101111111011010101101011101000011000001110100111101000001000110100000101000011100010001010001011011111110110110000001101011011110000100000110111110101110100110100010001001101011001011011011000001000000001000001011010010111101111000011011101111111001001110110101111101111100101110001010101000100110100001110101010010010001010101011001100111011101110000000110000111101111100100011111001110101010001111011110101100000111000000101001011101101000100010010001101111101110101111111011100101111110100010000100101100011101111000011100010101101101001101000100011001101011001101001000000011010100110111111101001111100001100111111111110001110011100101010100010010000100100101001110101100000010010110111111000001011000001111101010101100101101111010111010000011010111101000001101001111000001101111100001101010011101010000101111011000100001001111001000101100010111010");
        b = BigInt("1010100110101001011100010110000011011111000110010010010010111010110110110011000010110101010101011011110110110100100100111010010010101110101000100111001101011111011011110110011101000011000101011001101111000011100000010100101100000100010000011001001000100011011001000101011110101011100011011101010101000110110011111011001010101011001101011101000100101111011011000001011010000111000110110110001001000010100010111111000110000101000110101011110011011101101011111101110011100111100111011111000100100011000011111100010010100000101101110011011000000111011010111101101110100100111100101001010000101000110111110110101000101110011100000001011110111100111101011001100000011000011010000011100110000011110101101001110111010100110110011110000111111100101100011010000010101111011110110010100001101100110001110010101001100111101000110111001010001010101001110000110110111011101110001101111111110000000110100100101100111101011101101100000100000110001101101101110110000101100101011110001111000101010011011010101011001010110001001011100101001100");
        c = BigInt("1010100110101001011100010110000011011111000110010010010010111010110110110011000010110101010101011011110110110100100100111010010010101110101000100111001101011111011011110110011101000011000101011001101111000011100000010100101100000100010000011001001000100011011001000101011110101011100011011101010101000110110011111011001010101011001101011101000100101111011011000001011010000111000110110110001001000010100010111111000110000101000110101011110011011101101011111101110011100111100111011111000100100011000011111100010010100000101101110011011000000111011010111101101110100100111100101001010000101000110111110110101000101110011100000001011110111100111101011001100000011000011010000011100110000011110101101001110111010100110110011110000111111100101100011010000010101111011110110010100001101100110001110010101001100111101000110111001010001010101001110000110110111011101110001101111111110000000110100100101100111101011101101100000100111101000001101001111000001101111100001101010011101010000101111011000100001001111001000101100010111010");
    }

    cout<<"a = "<<a.getDigits()<<endl;
    cout<<"b = "<<b.getDigits()<<endl;
    cout<<"c = "<<c.getDigits()<<endl;


    LOG_TIME(begin);
    BigInt mod = a % b;
    LOG_TIME(end);
    cout<<"a % b = "<<mod.getDigits()<<endl;
    cout<<"Time mod: "<<TIME_DIFF(end, begin)<<MICRO_S<<endl;

    LOG_TIME(begin);
    BigInt mMod = alg->MulMod(a,b,c);
    LOG_TIME(end);
    cout<<"a*b mod c = "<<mMod.getDigits()<<endl;
    cout<<"Time mulMod: "<<TIME_DIFF(end, begin)<<MICRO_S<<endl;


    LOG_TIME(begin);
    BigInt pMod = alg->PowMod(a,b,c);
    LOG_TIME(end);
    cout<<"a^b mod c = "<<pMod.getDigits()<<endl;
    cout<<"Time powMod: "<<TIME_DIFF(end, begin)<<MICRO_S<<endl;

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
int main(int argc, char* argv[])
{
    // main_algorithm();
    //main_basic();
    //main_rsa();
    //main_inverse();
    main_compare();
    return 1;
}