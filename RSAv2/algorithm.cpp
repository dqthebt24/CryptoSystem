#include <algorithm>
#include <string>
#include <time.h>
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
