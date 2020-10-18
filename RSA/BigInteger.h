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
public:
    BigInteger(std::string binary);
    ~BigInteger();
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);
    friend BigInteger operator + (BigInteger a, BigInteger b);
};

