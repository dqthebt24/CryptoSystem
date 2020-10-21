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
	BigInteger a("1010100000000000000000000000000011111111100000000000000000011110100000000000001111111010101");
    BigInteger b("11111111111110000000000000000000001111111111110001011000110100001111110");
    std::cout<<"a="<<a<<std::endl;
    std::cout<<"b="<<b<<std::endl;

    std::cout<<"a > b ?"<< (a > b)<<std::endl;

    std::cout<<"a == b ?"<< (a == b)<<std::endl;
    std::cout<<"Compare: "<< a.Compare(b)<<";"<<a.Compare(a)<<";"<<b.Compare(a)<<std::endl;
    std::cout<<"Subtract: "<< a - b << std::endl;
    std::cout<<a + b<<std::endl;
}
