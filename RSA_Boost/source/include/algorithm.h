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

	/**
	 * \brief isPrime for testing if a number is a prime
	 * \details 
	 * 
	 * \param n The number to check
	 * \return true if the number is prime, else return false
	 */
	bool isPrime(number_t n);

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

	/**
	 * \brief Generate strong prime
	 * 
	 * \param length
	 * \return The strong prime 
	 */
	number_t GenStrongPrime(const int length);

	/**
	 * \brief Function calculate d where ed = 1 [mod phi] for RSA
	 *
	 * \param e     The e is always a prime, so that gcd(e, phi) = 1
	 * \param phi   The phi number
	 * \return d
	 */
	number_t GetEInverse(const number_t& e, const number_t& phi);

	/**
	 * \brief AlgBinaryBezout. 
	 *  Input a, b. 
	 *  Output x,y,g = gcd(a,b) | ax + by = g
	 * 
	 * \details Follow 1.49 Book 1, page 26
	 *
	 * \param a	Number a
	 * \param b	Number b
	 * \param x	Number x
	 * \param y	Number y
	 * \param g	GCD(a,b)
	 * \return 
	 */
	void AlgBinaryBezout(const number_t& a, const number_t& b, number_t& x, number_t& y, number_t& g);
};

