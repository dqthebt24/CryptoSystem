#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include "bigint.h"

using namespace std;

int main()
{
    BigInt a(100);
    cout << &a.mDigits <<endl;
    cout << "A=" << a.getDigits() << endl;
    //cout << "B=" << b.getDigits() << endl;
    return 1;
}
