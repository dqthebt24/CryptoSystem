#include <iostream>
#include <string>
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
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    sleepcp(1000);
    begin = std::chrono::steady_clock::now();
    BigInt b(2048);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    cout << "A=" << a.getDigits() << endl;
    cout << "B=" << b.getDigits() << endl;
    cout << "TEST111111\n";
    BigInt c = b;
    cout << "TEST2222222\n";
    cout << "C=" << c.getDigits() << endl;
    return 1;
}
