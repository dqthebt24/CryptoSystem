/*****************************************************************//**
 * \file   BigInteger.h
 * \brief  Prototypes
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/
#pragma once
#include "biginteger.h"

class Algorithm {
private:
	static Algorithm* mInstance;

public:
	static Algorithm* GetInstance();
	BigInteger MulMod(const BigInteger x, const BigInteger y, const BigInteger n);
	BigInteger PowMod(const BigInteger x, const BigInteger p, const BigInteger n);
};