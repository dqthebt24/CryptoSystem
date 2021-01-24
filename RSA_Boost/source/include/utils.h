#pragma once
#include <chrono>
#include "algorithm.h"

/**
 * \brief Convert number_t to binary string
 * 
 * \param n The number to be converted
 * \return The binary string
 */
std::string NumToBinary(const number_t& n);

/**
 * \brief Cross-platform sleep function
 * 
 * \param milliseconds The number of m-seconds
 */
void sleepcp(int milliseconds); // Cross-platform sleep function
