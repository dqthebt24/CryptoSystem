#pragma once
#include "bigint.h"
class Algorithm {
private:
	static Algorithm* mInstance;

public:
	static Algorithm* GetInstance();

	/**
	 * \brief Generate a binary string with size is 'length'
	 * 
	 * \param length	The size of the string
	 * \return binary string
	 */
	char* GenBinaryString(int length);

	/**
	 * \brief Calculates x*y
	 *
	 * \param x
	 * \param y
	 * \return x*y
	 */
	BigInt Mul(const BigInt& x, const BigInt& y);

	/**
	 * \brief Calculates x*y mod n
	 *
	 * \param x
	 * \param y
	 * \param n
	 * \return x*y mod n
	 */
	BigInt MulMod(const BigInt& x, const BigInt& y, const BigInt& n);
	
	/**
	 * \brief Calculates x^p mod n
	 *
	 * \param x
	 * \param p
	 * \param n
	 * \return x^p mod n
	 */
	BigInt PowMod(const BigInt& x, const BigInt& p, const BigInt& n);

	/**
	 * \brief Function calculate d where ed = 1 [mod phi] for RSA
	 * \details Follow 1.49 Book 1, page 26
	 *
	 * \param e     The e is always a prime, so that gcd(e, phi) = 1
	 * \param phi   The phi number
	 * \return d
	 */
	BigInt GetEInverse(const BigInt& e, const BigInt& phi);

	/**
	 * \brief Function calculate x/y
	 * \details This version only for x >= y
	 *
	 * \param x A binary number
	 * \param y A binary number
	 * \return The binary result
	 */
	BigInt Div(const BigInt& x, const BigInt&y);
};

