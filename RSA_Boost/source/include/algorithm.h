#pragma once
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include "define.h"

namespace mp = boost::multiprecision;
typedef mp::number<mp::cpp_int_backend<4096, 4096, mp::signed_magnitude, mp::unchecked, void> >  number_t; // int4096_t

class Algorithm {
private:
	static Algorithm* mInstance;

	number_t binaryToDecimal(std::string n);

public:
	static Algorithm* GetInstance();
	/**
	 * \brief Generate a binary string with size is 'length'
	 *
	 * \param length	The size of the string
	 * \return binary string
	 */
	std::string GenBinaryString(int length);

	/**
	 * \brief Generate a number with the size is 'length'
	 *
	 * \param length	The size
	 * \return The number
	 */
	number_t GenerateNumber(int length);

	/**
	 * \brief Calculates x*y mod n
	 *
	 * \param x
	 * \param y
	 * \param n
	 * \return x*y mod n
	 */
	number_t MulMod(const number_t& x, const number_t& y, const number_t& n);

	/**
	 * \brief Calculates x^p mod n
	 *
	 * \param x
	 * \param p
	 * \param n
	 * \return x^p mod n
	 */
	number_t PowMod(const number_t& x, const number_t& p, const number_t& n);

	/**
	 * \brief Generate a prime
	 *
	 * \param length	The length of the prime
	 * \return The prime
	 */
	number_t GenPrime(const int length);
};

