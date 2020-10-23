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

	if (n.Compare(BigInteger("0")) != 1 || n.Compare(BigInteger("1")) || x.Compare(BigInteger("0")) != 1 || p.Compare(BigInteger("0")) == -1) {
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
