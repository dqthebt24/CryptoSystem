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
    int bits = 512;
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
    BigInt c = a+b;
    end = std::chrono::steady_clock::now();
    cout << "C= " << c.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    bool res = a >= b;
    end = std::chrono::steady_clock::now();

    cout<<"Compare:"<<(a > b)<<";"<<(b > a)<<";"<<(a>=b)<<endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    if (!res) {
        return;
    }

    // Test subtraction
    begin = std::chrono::steady_clock::now();
    BigInt d = a - b;
    end = std::chrono::steady_clock::now();
    cout<<"D: "<<d.getDigits()<<endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt e = a % b;
    end = std::chrono::steady_clock::now();
    cout<<"E: "<<e.getDigits()<<endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
}

void main_algorithm()
{
    int bits = 1024;
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();

    BigInt a(bits);
    sleepcp(1000);
    BigInt b(bits);
    sleepcp(1000);
    BigInt c(bits);

    cout<<"A= "<<a.getDigits()<<endl;
    cout<<"B= "<<b.getDigits()<<endl;
    cout<<"C= "<<c.getDigits()<<endl;

    begin = std::chrono::steady_clock::now();
    BigInt sum = a + b;
    end = std::chrono::steady_clock::now();
    cout<<"Sum= "<<sum.getDigits()<<endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt d = algorithm->MulMod(a, b, c);
    end = std::chrono::steady_clock::now();
    cout<<"D= "<<d.getDigits()<<endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    BigInt e = algorithm->PowMod(a, b, c);
    end = std::chrono::steady_clock::now();
    cout << "E= " << d.getDigits() << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
}

void main_prime()
{
    int bits = 256;
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();
    vector<BigInt> bases{BigInt(5), BigInt(7)};
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
}
int main()
{
    //main_algorithm();
    //main_basic();
    main_prime();
    return 1;
}