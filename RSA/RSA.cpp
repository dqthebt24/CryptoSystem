/*****************************************************************//**
 * \file   RSA.cpp
 * \brief  Main file test RSA algorithm
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/
#include <iostream>
#include "BigInteger.h"

int main()
{
    BigInteger a("100100111000000000000000000000000100000000000000000001011111111111111110000011110");
    BigInteger b("11");
    std::cout << a + b;
}
