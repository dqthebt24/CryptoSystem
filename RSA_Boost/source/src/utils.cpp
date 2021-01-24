#include "utils.h"

void sleepcp(int milliseconds)
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < time_end) {
    }
}

std::string NumToBinary(const number_t& n)
{
	std::string r;
    number_t tmp = n;
    while(tmp != 0)
    {
        r = (tmp % 2 == 0 ? "0":"1") + r;
        tmp /= 2;
    }
    return r;
}