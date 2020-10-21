/*****************************************************************//**
 * \file   BigInteger.h
 * \brief  Prototypes
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/
#pragma once
#include "define.h"
class BigInteger {
private:
	std::string mDigits;
	void free();
	void format();
public:
	BigInteger(std::string binary);
	~BigInteger();
	int Compare(const BigInteger a);
	friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);
	friend BigInteger operator + (const BigInteger a, const BigInteger b);
	friend BigInteger operator - (const BigInteger a, const BigInteger b);
	friend BigInteger operator<<(const BigInteger a, int n);
	friend BigInteger operator>>(const BigInteger a, int n);
	friend bool operator > (const BigInteger a, const BigInteger b);
	friend bool operator == (const BigInteger a, const BigInteger b);
};

