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
    char add(char c1, char c2, bool& isRemembered);
public:
    BigInteger(std::string binary);
    ~BigInteger();
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);
    friend BigInteger operator + (BigInteger a, BigInteger b);
};

