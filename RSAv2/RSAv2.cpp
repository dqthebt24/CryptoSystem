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
    std::chrono::steady_clock::time_point begin, end;
    begin = std::chrono::steady_clock::now();
    BigInt a(2048);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
    sleepcp(1000);
    begin = std::chrono::steady_clock::now();
    BigInt b(2048);
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
    bool res = a > b;
    end = std::chrono::steady_clock::now();

    cout<<"Compare:"<<(a > b)<<";"<<(b > a)<<";"<<(a>=b)<<endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

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
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();

    BigInt a(1024);
    sleepcp(1000);
    BigInt b(1024);
    sleepcp(1000);
    BigInt c(1024);

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
}

int main() 
{
    main_algorithm();
    // main_basic();
    return 1;
}