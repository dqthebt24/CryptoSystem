#include <random>
#include <ctime>
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

/**
 * \brief MulMode(x,y,n)
 * \details Calculate x*y % n
 * 			This version only support x > 0, p > 0, n > 0
 * \param x BigInteger x
 * \param y BigInteger y
 * \param n BigInteger n
 * \return x*y % n
 */
BigInteger Algorithm::MulMod(const BigInteger x, const BigInteger y, const BigInteger n)
{
	BigInteger res;
	
	if (x.Compare(BigInteger("0")) != 1 || y.Compare(BigInteger("0")) != 1 || n.Compare(BigInteger("0")) != 1) {
		return res;
	}

	BigInteger znX = x % n;
	BigInteger znY = y % n;
	string strZnY = znY.getDigits();
	int lenY = strZnY.length();

	if (strZnY[lenY - 1] == '1') {
		res = znX;
	}

	for (int i = 1; i < lenY; i++) {
		znX = (znX << 1) % n;

		if (strZnY[lenY - i -1] == '1') {
			res = (res + znX) % n;
		}
	}

	return res;
}

/**
 * \brief PowMod(x,p,n)
 * \details Calculate (x^p) % n
 * 			This version only support x > 0, p > 0, n > 0
 * \param x BigInteger x
 * \param p BigInteger p
 * \param n BigInteger n
 * \return (x^p) % n
 */
BigInteger Algorithm::PowMod(const BigInteger x, const BigInteger p, const BigInteger n) {
	BigInteger res("1");

	if (n.Compare(BigInteger("0")) != 1 || x.Compare(BigInteger("0")) != 1 || p.Compare(BigInteger("0")) == -1) {
		return BigInteger("0");
	}

	if (p == BigInteger("0")) {
		return res;
	}

	BigInteger znX = x % n;
	string strP = p.getDigits();
	int lenP = strP.length();

	if (strP[lenP - 1] == '1') {
		res = znX;
	}

	for (int i = 1; i < lenP; i++) {
		znX = MulMod(znX, znX, n);
		if (strP[lenP - i - 1] == '1') {
			res = MulMod(res, znX, n);
		}
	}

	return res;
}

/**
 * \brief GenBigInteger(n)
 * 
 * \details Generate a BigInteger number with n digits
 * 
 * \param digits Number of digits
 * \return BigInteger number
 */
BigInteger Algorithm::GenBigInteger(int digits) 
{
	string str = "1";
	srand(time(nullptr));
	for (int i = 1; i < digits; i++) {
		int x = rand() % 2;
		str.push_back(x == 0 ? '0' : '1');
	}
	return BigInteger(str);
}

/**
 * \brief PrimeTest(n)
 * \details Check if a number is prime or not
 * 			This version only support n > 2
 * \param 	n 		: BigInteger n
 * \return 	true	: n is a prime
 * 			false	: n is not a prime
 */
bool Algorithm::PrimeTest(const BigInteger n) {
	
	std::vector<BigInteger> bases{BigInteger("10"), BigInteger("11"), BigInteger("101"), BigInteger("111"), BigInteger("10111101")};

	if (n == BigInteger("10")) {
		return true;
	}

	for (int i = 0; i< bases.size(); i++) {
		if (PowMod(bases[i], n - BigInteger("1"), n).Compare(BigInteger("1")) != 0) {
			return false;
		}
	}

	return true;
}
