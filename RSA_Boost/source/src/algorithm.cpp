#include "algorithm.h"

using namespace std;

Algorithm* Algorithm::mInstance = nullptr;

Algorithm* Algorithm::GetInstance()
{
    if (mInstance == nullptr) {
        mInstance = new Algorithm();
    }
    return mInstance;
}

number_t Algorithm::binaryToDecimal(string n)
{
    string num = n;
    number_t dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    number_t base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

string Algorithm::GenBinaryString(int length)
{
    srand((unsigned int)time(nullptr));
    auto randchar = []() -> char {
        const char charset[] = "01";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };

    string str(length, 0);
    generate_n(str.begin(), length, randchar);

    str[0] = '1';
    cout << "Str: " << str << endl;
    return str;
}

number_t Algorithm::GenerateNumber(int length)
{
    return binaryToDecimal(GenBinaryString(length));
}

number_t Algorithm::MulMod(const number_t& x, const number_t& y, const number_t& n)
{
    if (x == 0 || y == 0 || n <= 0) {
        return 0;
    }

    /*number_t X = x;
    number_t Y = y;
    number_t res = 0;

    if (y % 2 == 1) {
        res = X;
    }

    Y >>= 1;
    while( Y > 0) {
        X <<= 1;

        if (Y % 2 == 1) {
            res += X;
        }

        Y >>= 1;
    }
    return res % n;*/

    number_t mul = x * y;

    return mul % n;
}

number_t Algorithm::PowMod(const number_t& x, const number_t& p, const number_t& n)
{
    if (x == 0 || n <= 0 || p < 0) {
        return 0;
    } else if (p == 0) {
        return 1 % n;
    }

    number_t znX = x % n, res = 1, tmp = p;

    if (p % 2 == 1) {
        res = znX;
    }

    tmp >>= 1;
    while (tmp > 0) {
        znX = MulMod(znX, znX, n);

        if (tmp % 2 == 1) {
            res = MulMod(res, znX, n);
        }

        tmp >>= 1;
    }
    return res;
}

#include <chrono>
number_t Algorithm::GenPrime(const int length)
{
    std::chrono::steady_clock::time_point begin, end;
    vector<number_t> bases{ 2, 5, 7 };
    number_t prime, tmp = GenerateNumber(length);
    bool found = false;

    begin = std::chrono::steady_clock::now();
    while (!found) {
        prime = 6*tmp + 1;

        found = true;
        for (int i = 0; i < (int)bases.size(); i++) {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            number_t res = PowMod(bases[i], prime - 1, prime);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            cout << "   RES: " << res << endl;
            std::cout << "   Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

            if (res != 1) {
                found = false;
                break;
            }
        }

        if (!found) {
            tmp += 2;
        }
    }

    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    cout << "Prime is: " << prime << endl;
    return prime;
}
