/*****************************************************************//**
 * \file   BigInteger.cpp
 * \brief  BigInteger implementation
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/

#include <iostream>
#include <string>
#include "BigInteger.h"
#include "calculator.h"

using namespace std;

void BigInteger::free()
{
	mDigits = "0";
}

void BigInteger::format()
{
	int idx = -1;
	for (int i = 0 ; i < mDigits.length(); i++) {
		idx++;
		if (mDigits[i] == '1') {
			break;
		}
	}

	if (idx > 0) {
		mDigits = mDigits.substr(idx);
	}
}

BigInteger BigInteger::modulo(const BigInteger a, const BigInteger n) const
{
	BigInteger res;
	res = a;
	while (res > n) {
		res = res - n;
	}
	return res == n ? BigInteger("0") : res;
}

BigInteger::BigInteger() : mDigits("0")
{
}

BigInteger::BigInteger(std::string binary)
{
	bool isIncorrectFormat = false;
	if (binary.length() > 0) {
		for (int i = 0; i < (int)binary.length(); i++) {
			if (binary[i] != '0' && binary[i] != '1') {
				isIncorrectFormat = true;
				break;
			}
		}
		mDigits = binary;
		format();
	}
	return;
}

BigInteger::~BigInteger()
{
	free();
}

/**
 * \brief Function compare this number with other BigInteger number
 * 
 * \param BigInteger a: A number to compare
 * \return 
 * 		 0: equal
 * 		 1: larger than the number
 * 		-1: smaller than the number
 */
int BigInteger::Compare(const BigInteger a) const 
{
	int result = 0;
	BigInteger number(mDigits);
	if (number > a){
		result = 1;
	} else if (number == a) {
		result = 0;
	} else {
		result = -1;
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& number)
{
	out << number.mDigits;
	return out;
}

BigInteger BigInteger::operator+(const BigInteger n) const
{
	string res = "";
	bool isRemembered = false;
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();
	int lenMax = (int)(MAX(len, lenN));
	for (int i = 1; i <= lenMax; i++) {
		if (i > len) {
			if (isRemembered)
				res.push_back(add(n.mDigits[lenN - i], '0', isRemembered));
			else {
				res.push_back(n.mDigits[lenN - i]);
			}
		} else if (i > lenN) {
			if (isRemembered)
				res.push_back(add(this->mDigits[len - i], '0', isRemembered));
			else {
				res.push_back(this->mDigits[len - i]);
			}
		} else {
			res.push_back(add(this->mDigits[this->mDigits.length() - i], n.mDigits[n.mDigits.length() - i], isRemembered));
		}
	}
	if (isRemembered) {
		res.push_back('1');
	}
	return BigInteger(string(res.rbegin(), res.rend()));
}

/**
 * \brief Function do subtraction
 * \details This version of code support "*this" - n with "*this" >= n only
 *			"*this": Minuend
 *          
 * \param n Subtrahend
 * 
 * \return Difference
 */
BigInteger BigInteger::operator-(const BigInteger n) const 
{
	string res = "";
	bool isRemembered = false;
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();

	if (n > *this) {
		return BigInteger("0");
	}

	for (int i = 1; i <= len; i++) {
		if (i > n.mDigits.length()) {
			if (isRemembered) {
				res.push_back(sub(this->mDigits[len - i], '0', isRemembered));
			} else {
				res.push_back(this->mDigits[len - i]);
			}
		} else {
			res.push_back(sub(this->mDigits[len - i], n.mDigits[lenN - i], isRemembered));
		}
	}

	return BigInteger(string(res.rbegin(), res.rend()));
}

/**
 * \brief Function do shift to left n bits
 * \details Current version not support overload bits
 * 
 * \param n Number of bits
 * \return the result
 */
BigInteger BigInteger::operator<<(const int n) const 
{
	if (n > 0) {
		BigInteger result(this->mDigits);
		for (int i = 0; i < n; i++) {
			result.mDigits.push_back('0');
		}
		// return BigInteger(result.mDigits.substr(n));
		return result;
	}

	return BigInteger(this->mDigits);
}

BigInteger BigInteger::operator>>(const int n) const 
{
	if( n > 0) {
		return BigInteger(this->mDigits.substr(0, this->mDigits.length() - n));
	}
	return BigInteger(this->mDigits);
}

bool BigInteger::operator>(const BigInteger n) const 
{
	bool result = false;
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();

	if (len > lenN) {
		result = true;
	} else if (lenN > len) {
		result = false;
	} else {
		for (int i = 0; i < len; i++) {
			if (this->mDigits[i] != n.mDigits[i]) {
				if (this->mDigits[i] == '0') {
					result = false;
				} else {
					result = true;
				}
				break;
			}
		}
	}

	return result;
}

/**
 * \brief This function calculates *this % n
 * \details Current version only supports *this > 0, n > 0
 * 
 * \param n Input n is a BigInteger number
 * 
 * \return Result of *this % n
 */
BigInteger BigInteger::operator%(const BigInteger n) const
{
	BigInteger res;
	if (*this == BigInteger("0") || n == BigInteger("0") || *this == n) {
		return res;
	}

	if (n > *this) {
		res = *this;
	} else if (*this > n) {
		int len = mDigits.length();
		int lenN = n.mDigits.length();
		// BigInteger previous(mDigits.substr(len - lenN + 1));
		BigInteger previous("1");
		
		if (mDigits[len - 1] == '1') {
			res = previous;
		}

		// res = previous;
		for (int i = len - 1; i > 0; i--) {
			// Calculate (previous*2 % n)
			previous = modulo(previous << 1, n);

			// Calculate res = (res + previous) % n
			if (mDigits[i - 1] == '1') {
				res = modulo(res + previous, n);
			}
		}

	}

	return res;
}

bool BigInteger::operator == (const BigInteger n) const 
{
	return mDigits.compare(n.mDigits) == 0;
}