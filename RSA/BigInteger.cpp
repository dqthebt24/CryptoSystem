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
int BigInteger::Compare(const BigInteger a) {
	int result = 0;
	BigInteger number(this->mDigits);
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

BigInteger operator+(const BigInteger a, const BigInteger b)
{
	string res = "";
	bool isRemembered = false;
	int lenA = a.mDigits.length();
	int lenB = b.mDigits.length();
	int lenMax = (int)(MAX(lenA, lenB));
	for (int i = 1; i <= lenMax; i++) {
		if (i > lenA) {
			if (isRemembered)
				res.push_back(add(b.mDigits[lenB - i], '0', isRemembered));
			else {
				res.push_back(b.mDigits[lenB - i]);
			}
		} else if (i > lenB) {
			if (isRemembered)
				res.push_back(add(a.mDigits[lenA - i], '0', isRemembered));
			else {
				res.push_back(a.mDigits[lenA - i]);
			}
		} else {
			res.push_back(add(a.mDigits[a.mDigits.length() - i], b.mDigits[b.mDigits.length() - i], isRemembered));
		}
	}
	if (isRemembered) {
		res.push_back('1');
	}
	return BigInteger(string(res.rbegin(), res.rend()));
}

/**
 * \brief Function do subtraction
 * \details This version of code support a - b with a >= b only
 * 
 * \param a Minuend
 * \param b Subtrahend
 * 
 * \return Difference
 */
BigInteger operator - (const BigInteger a, const BigInteger b) {
	string res = "";
	bool isRemembered = false;
	int lenA = a.mDigits.length();
	int lenB = b.mDigits.length();

	if (b > a) {
		return BigInteger("0");
	}

	for (int i = 1; i <= lenA; i++) {
		if (i > b.mDigits.length()) {
			if (isRemembered) {
				res.push_back(sub(a.mDigits[lenA - i], '0', isRemembered));
			} else {
				res.push_back(a.mDigits[lenA - i]);
			}
		} else {
			res.push_back(sub(a.mDigits[lenA - i], b.mDigits[lenB - i], isRemembered));
		}
	}

	return BigInteger(string(res.rbegin(), res.rend()));
}

BigInteger operator<<(const BigInteger a, int n) {
	if (n > 0) {
		BigInteger result(a.mDigits);
		for (int i = 0; i < n; i++) {
			result.mDigits.push_back('0');
		}
		return BigInteger(result.mDigits.substr(n));
	}

	return BigInteger(a.mDigits);
}

BigInteger operator>>(const BigInteger a, int n) {
	if( n > 0) {
		return BigInteger(a.mDigits.substr(0, a.mDigits.length() - n));
	}
	return BigInteger(a.mDigits);
}

bool operator > (const BigInteger a, const BigInteger b) {
	bool result = false;
	int lenA = a.mDigits.length();
	int lenB = b.mDigits.length();

	if (lenA > lenB) {
		result = true;
	} else if (lenB > lenA) {
		result = false;
	} else {
		for (int i = 0; i < lenA; i++) {
			if (a.mDigits[i] != b.mDigits[i]) {
				if (a.mDigits[i] == '0') {
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

bool operator == (const BigInteger a, const BigInteger b) {
	return a.mDigits.compare(b.mDigits) == 0;
}