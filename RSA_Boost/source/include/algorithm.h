#pragma once
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include "define.h"

namespace mp = boost::multiprecision;
typedef mp::number<mp::cpp_int_backend<4096, 4096, mp::signed_magnitude, mp::unchecked, void> >  number_t; // int4096_t

struct RSA_INFO{
	number_t p, q, n, phi, e, d;

	RSA_INFO(number_t _p, number_t _q, number_t _n, number_t _phi, number_t _e, number_t _d) {
		p = _p;
		q = _q;
		n = _n;
		phi = _phi;
		e = _e;
		d = _d;
	}
};

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

	/**
	 * \brief Generate e and d for RSA
	 * 
	 * \param p The prime p
	 * \param q The prime q
	 * \param n The number phi
	 * \param n p*q
	 * \return e and d
	 */
	void genKey(const number_t& p, const number_t& q, const number_t& phi, const number_t& n, number_t&e, number_t& d);

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
	 * \brief Find x that ax = 1 [mod b]
	 * \details a, b are arbitrary numbers
	 * 
	 * \param a The first number
	 * \param b The second number
	 * 
	 * \return Number x
	 */
	number_t GetInverse(const number_t& a, const number_t& b);

	/**
	 * \brief Solve Chinese Remainder Theorem.
	 * 
	 * Find x where x = a1 [mod n1], x = a2 [mod n2], ....
	 * 
	 * \details 
	 * 
	 * \param lstN Array numbers lstN = [n1, n2, ..., nk]
	 * \param lstA Array numbers lstA = [a1, a2, ..., ak]
	 * 
	 * \return The solution x
	 */
	number_t SolveCrt(const std::vector<number_t> lstN, const std::vector<number_t> lstA);

	/**
	 * \brief Binary Bezout algorithm
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

	/**
	 * \brief RSA Fast decrypt using CRT
	 * \details 
	 * 
	 * \param c The encrypted message
	 * \param d The number d | ed = 1 [mod phi]
	 * \param n The number n | n = pq
	 * \param p The prime p
	 * \param q The prime q
	 * \return The decrypted message
	 */
	number_t RsaDecryptCrt(const number_t& c, const number_t& d, const number_t& n, const number_t& p, const number_t& q);

	/**
	 * \brief Gen key for RSA
	 * \details 
	 * 
	 * \param len Number bits length of p and q
	 * \return The info for RSA (p, q, n, phi, e, d)
	 */
	RSA_INFO RsaGenKey(const int len);

	/**
	 * \brief Encrypt the message using RSA
	 * 
	 * \param m	The message to be encrypted
	 * \param e The public key
	 * \param n The public number
	 * \return Encrypted version of m
	 */
	number_t RsaEncrypt(const number_t& m, const number_t& e, number_t& n);

	/**
	 * Decrypt the encrypted message using RSA
	 * 
	 * \param c		The encrypted message
	 * \param info	RSA info (p, q, n, phi, e, d)
	 * \return		The decrypted message
	 */
	number_t RsaDecrypt(const number_t& c, const RSA_INFO& info);
};

