#pragma once

#ifndef DEBUG
#define LOG(x) 
#else
#define LOG(x) do { std::cout << x << std::endl; } while (0)
#endif

#define MICRO_S "[\xC2\xB5s]"