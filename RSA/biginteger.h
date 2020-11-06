/*****************************************************************//**
 * \file   BigInteger.h
 * \brief  Prototypes
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include "define.h"
class BigInteger {
private:
	std::string mDigits;
	void free();
	void format();
	BigInteger modulo(const BigInteger a, const BigInteger n) const;
	

public:
	std::vector<BigInteger> Split(const BigInteger n, const int width) const;
	BigInteger();
	BigInteger(std::string binary);
	~BigInteger();
	void Set( int pos,  char value) ;
	int Compare(const BigInteger a) const;
	bool operator>(const BigInteger n) const;
	bool operator==(const BigInteger n) const;
	bool operator!=(const BigInteger n) const;
	BigInteger operator+(const BigInteger n) const;
	BigInteger operator-(const BigInteger n) const;
	BigInteger operator&(const BigInteger n) const;
	BigInteger operator^(const BigInteger n) const;
	BigInteger operator<<(const int n) const;
	BigInteger operator>>(const int n) const;
	BigInteger operator%(const BigInteger n) const;
	friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);

	int getLen() const {return mDigits.length();}
	std::string getDigits() const {return mDigits;}
};

