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

char BigInteger::add(char c1, char c2, bool& isRemembered)
{
	return '0';
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
		if (!isIncorrectFormat) {
			mDigits = binary;
		}
	}
	return;
}

BigInteger::~BigInteger()
{
	free();
}

std::ostream& operator<<(std::ostream& out, const BigInteger& number)
{
	out << number.mDigits;
	return out;
}

BigInteger operator+(BigInteger a, BigInteger b)
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
	return string(res.rbegin(), res.rend());
}
