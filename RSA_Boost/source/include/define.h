#pragma once

#ifndef DEBUG
#define LOG(x) 
#else
#define LOG(x) do { std::cout << "[" << __FUNCTION__<<"] " << x << std::endl; } while (0)
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define MICRO_S "[\xE6s]"
#else
#define MICRO_S "[\xC2\xB5s]"
#endif