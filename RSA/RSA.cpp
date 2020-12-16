/*****************************************************************//**
 * \file   RSA.cpp
 * \brief  Implement algorithms for RSA
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/
#include <iostream>
#include <chrono>
#include <time.h>
#include "biginteger.h"
#include "algorithm.h"

using namespace std;

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < time_end) {
    }
}
#include <boost/dynamic_bitset.hpp>

boost::dynamic_bitset<> Add(boost::dynamic_bitset<>& x, boost::dynamic_bitset<>& y, int n)
{
    boost::dynamic_bitset<> carry;
    boost::dynamic_bitset<> zero(n,0);
    while (y != zero) {
        // carry now contains common  
        //set bits of x and y  
        carry = x & y;

        // Sum of bits of x and y where at  
        //least one of the bits is not set  
        x = x ^ y;

        // Carry is shifted by one so that adding  
        // it to x gives the required sum  
        y = carry << 1;
    }
    return x;
}

void populateBitSet(std::string& buffer, boost::dynamic_bitset<unsigned char>& bitMap)
{
    bitMap = boost::dynamic_bitset<unsigned char>(buffer);
}

int main()
{
    
    int bits = 256;
    std::chrono::steady_clock::time_point begin, end;
    Algorithm* algorithm = Algorithm::GetInstance();


    /*string str1 = algorithm->GenBigInteger(bits).getDigits();
    sleepcp(10000);
    string str2 = algorithm->GenBigInteger(bits).getDigits();

    boost::dynamic_bitset<> B1(str1);
    boost::dynamic_bitset<> B2(str2);
    B1.resize(bits+1);
    B2.resize(bits+1);
    cout << "B1:" << B1 << endl;
    cout << "B2:" << B2 << endl;
    begin = std::chrono::steady_clock::now();
    cout <<"Res:"<< Add(B1, B2, bits+1) << endl;
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;*/

    /* Init big number*/
    /*BigInteger a("10111101101110111101100000001001110010100001100100011011110000111010111011111101101010111110011110011110001111000100000011010100010011101001010100001010001011111010101001101111001011000110100010000001010010101110111111011101111010000001000001111010000001100111110001110010111001111110000101111011001011110100010011101111111010100000111001101100101101111011001010100101011000110101100010001001100011000001011000101111010010111101101110110101111111000111110110111001011110010011011001001011001011011100101011011001001010111100100001110000101001110001001010011010110110100111100000011110101010011000101010001001111101111101101110111101011001111001000100100110000111110100111101000000001110011101011011101110110000000001100011111100001011010101100110000111101000111001101000010010000001001110110010111111011000001000010101000111110011010100110000100000111101010111010010101011011111010001001111111100101110001100110100010010100100011011000101000011110101011001001010010101001010100000000011101111000001101111001001000000011110011");
    BigInteger b("1100010000000111110011100101111000101010101100000000110101110100110111001010100000101011101111010001001110001111011000110010101110111001100100000111101010101110100101011011001111011001000000001000001010001101010011001010011000101110001010000111111111110001110001110011111111011010100001101100111000010011110110110001011010011111011000111111011000110110011000000001010001111000011100101010");*/

    /*BigInteger a("1100101101001001110001000101111001000011010110101101011000111000000001010011011101011111101110001101011100100010110110111000101011101110110000010111001100010100100110000101001010001110111000011110001111010011010110100111101100110111011011011000001111010001001000001110100011000011100111001110011111010000110111000011000000010111000000111011111100100101101111000101011111011010000011010101001111011010011100010111011000111100110111000111001011111001011000011111010010111001110001001111000001111010011100000010001010001101101000011100100111111001010010100000100100100000010001100101011010001101010001110011101110101111110001110010111111010110011111000011001001110110100101101010001000010100011110001101110100110101011000100100000111011000110010110000001001100101111011001001000001001001110011101001101100001010110001110010101001101010001001000011101010111110100001101111000011100000001010000101010010110001010100110111100010010101100000111001101010000110101000010110011110111100101111000100011110010001001001111000010001111111");*/
    /*BigInteger b("1100010101111110010110000111011011110111101101010101101001010010000011010001000011110011001000001010110000001100011010001000001101010100011011011111100001111001100111100001100011111100011000111110111101100101101101011111100011011000110010111001011111111001101010001011111011001111001010010101001000010001010000000100100010001111010100111000001110001001011001000101011110001100111111010111000010101000111101110101011101101011101110001110000001000101010111100101110010011101110110111001100000110100011100011000000100111100110000011000100000000111111010011111000100111101110010100101111001101011001010101101100000110010000011000010111100001100001111011111111000100001100010001101001010000100111110111100111011000101001101100110010100001010000100100010111111111011111101000101010000010101011101100100100100011100111101010010111001000110011010000100010000100000011010100011100010110011111010110101000111000101001110110011011010100100111001010000000011001110010111101111011100001111011001001011101001111001111011000001101100101011");*/
    ///* Generate big number */
    begin = std::chrono::steady_clock::now();
    BigInteger a = algorithm->GenBigInteger(bits);
    end = std::chrono::steady_clock::now();
    std::cout << "a=" << a << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
    
    sleepcp(1000);
    begin = std::chrono::steady_clock::now();
    BigInteger b = algorithm->GenBigInteger(bits);
    end = std::chrono::steady_clock::now();
    std::cout << "b=" << b << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
    
    sleepcp(1000);
    BigInteger n = algorithm->GenBigInteger(bits);
    /*BigInteger c(a.getDigits());*/

    //std::cout << "b=" << b << std::endl;
    std::cout << "n=" << n << std::endl;

    /*BigInteger a("1010001011101110101111101111111110001000001000101110111001110001011110101110000010110101110001110110011001001010100110010100011101110011001");
    BigInteger b("101011101");

    begin = std::chrono::steady_clock::now();
    std::cout << "a + b     " << a % b << std::endl;*/
    // end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    //begin = std::chrono::steady_clock::now();
    //c += b;
    //std::cout << "a + b     " << c << std::endl;
    //end = std::chrono::steady_clock::now();
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    //c = a;
    //begin = std::chrono::steady_clock::now();
    //std::cout << "a - b     " << a - b << std::endl;
    //end = std::chrono::steady_clock::now();
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    //begin = std::chrono::steady_clock::now();
    //c -= b;
    //std::cout << "a - b     " << c << std::endl;
    //end = std::chrono::steady_clock::now();
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;



    begin = std::chrono::steady_clock::now();
    BigInteger bigIntC = a % b;
    end = std::chrono::steady_clock::now();
    std::cout << "a%b         " << bigIntC << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    //c = a;
    //begin = std::chrono::steady_clock::now();
    //c %= b;
    //std::cout << "a%b         " << c << std::endl;
    //end = std::chrono::steady_clock::now();
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    ///*std::cout << "MulMod1: " << algorithm->MulMod(BigInteger("10"), BigInteger("111"), BigInteger("11")) << endl;*/
    begin = std::chrono::steady_clock::now();
    std::cout << "MulMod: " << algorithm->MulMod(a, b,n) << std::endl;
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

    begin = std::chrono::steady_clock::now();
    std::cout << "PowMod: " << algorithm->PowMod(a, b,n) << std::endl;
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;    
}