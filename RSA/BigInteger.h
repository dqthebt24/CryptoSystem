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
	BigInteger modulo(const BigInteger a, const BigInteger n) const;

public:
	BigInteger();
	BigInteger(std::string binary);
	~BigInteger();
	int Compare(const BigInteger a) const;
	bool operator>(const BigInteger n) const;
	bool operator==(const BigInteger n) const;
	BigInteger operator+(const BigInteger n) const;
	BigInteger operator-(const BigInteger n) const;
	BigInteger operator<<(const int n) const;
	BigInteger operator>>(const int n) const;
	BigInteger operator%(const BigInteger n) const;
	friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);
};

