#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <chrono>
#include "bigint.h"

using namespace std;
void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < time_end) {
    }
}

int main()
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

    return 1;
}
