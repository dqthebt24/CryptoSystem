#pragma once

#ifndef DEBUG
#define LOG(x)
#define LOG_TIME(x)
#define TIME_DIFF(x,y)
#else
#define LOG(x) do { std::cout << "[" << __FUNCTION__<<"] " << x << std::endl; } while (0)
#define LOG_TIME(x) (x=std::chrono::steady_clock::now())
#define TIME_DIFF(x,y) (std::chrono::duration_cast<std::chrono::microseconds>(x-y).count())
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define MICRO_S "[\xE6s]"
#else
#define MICRO_S "[\xC2\xB5s]"
#endif
