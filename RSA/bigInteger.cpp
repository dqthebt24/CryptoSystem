/*****************************************************************//**
 * \file   BigInteger.cpp
 * \brief  BigInteger implementation
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/

#include <iostream>
#include <string>
#include "define.h"
#include "biginteger.h"
#include "calculator.h"

using namespace std;

void BigInteger::free()
{
	mDigits = "0";
}

void BigInteger::format()
{
	int idx = -1;
	for (int i = 0 ; i < (int)mDigits.length(); i++) {
		idx++;
		if (mDigits[i] == '1') {
			break;
		}
	}

	if (idx > 0) {
		mDigits = mDigits.substr(idx);
	}
}

BigInteger BigInteger::modulo(const BigInteger a, const BigInteger n) const
{
	BigInteger res;
	res = a;
	while (res > n) {
		res = res - n;
	}
	return res == n ? BigInteger("0") : res;
}

vector<BigInteger> BigInteger::Split(const BigInteger n, const int width) const
{
	vector<BigInteger> result;
	string str = n.getDigits();
	int len = str.length();
	int i = 1;
	for (; i*width <= len; i++) {
		result.push_back(str.substr(len - i*width, width));
	}

	if ((i - 1) * width < len) {
		result.push_back(BigInteger(str.substr(0, (len - (i - 1) * width))));
	}

	return result;
}

BigInteger::BigInteger() : mDigits("0")
{
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
		mDigits = binary;
		format();
	}
	return;
}

BigInteger::~BigInteger()
{
	free();
}

void BigInteger::Set(int pos, char value)
{
	if (mDigits.length() == 0 || pos >= (int) mDigits.length() || pos < 0
		|| (value != '0' && value != '1')) {
		return;
	}
	mDigits[pos] = value;
}

/**
 * \brief Function compare this number with other BigInteger number
 * 
 * \param BigInteger a: A number to compare
 * \return 
 * 		 0: equal
 * 		 1: larger than the number
 * 		-1: smaller than the number
 */
int BigInteger::Compare(const BigInteger a) const 
{
	int result = 0;
	BigInteger number(mDigits);
	if (number > a){
		result = 1;
	} else if (number == a) {
		result = 0;
	} else {
		result = -1;
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& number)
{
	out << number.mDigits;
	return out;
}

//#include <bitset>
//BigInteger BigInteger::operator+(const BigInteger n) const
//{
//	std::bitset<2048> x(this->mDigits);
//	std::bitset<2048> y(n.mDigits);
//	std::bitset<2048> carry;
//	while (y != 0) {
//		carry = x & y;
//		x = x ^ y;
//		y = carry << 1;
//	}
//	return BigInteger(x.to_string());
//}

//BigInteger BigInteger::operator+(const BigInteger n) const
//{
//	BigInteger x = *this;
//	BigInteger y = n;
//	BigInteger zero("0");
//	while (BigInteger(y.mDigits) != zero) {
//		BigInteger *carry = &(x & y);
//		x = x ^ y;
//		y = *carry << 1;
//	}
//	return x;
//}

BigInteger BigInteger::operator+(const BigInteger n) const
{
	string strN = n.getDigits();
	bool isRemembered = false;
	int len = (int)mDigits.length();
	int lenN = (int)strN.length();
	int lenMax = MAX(len, lenN);
	int idx = lenMax - 1;
	len--;
	lenN--;
	std::string res(lenMax, '0');
	char c = '0';

	while (len >= 0 || lenN >= 0) {
		char a = len >= 0 ? mDigits[len] : '0';
		char b = lenN >= 0 ? strN[lenN] : '0';
		res[idx] = ( (a ^ b) ^ c);
		c = ((a & b) | (a & c) | (b & c));
		idx--;
		len--;
		lenN--;
	}

	if (c == '1') {
		res.insert(0, "1");
	}
	return BigInteger(res);
}

BigInteger& BigInteger::operator+=(const BigInteger& n)
{
	string strN = n.getDigits();
	bool isRemembered = false;
	int len = (int)mDigits.length();
	int lenN = (int)strN.length();
	int lenMax = MAX(len, lenN);
	int idx = lenMax - 1;

	len--;
	lenN--;
	std::string res(lenMax, '0');
	while (len >= 0 || lenN >= 0) {
		res[idx] = add(len >= 0 ? mDigits[len] : '0', lenN >= 0 ? strN[lenN] : '0', isRemembered);
		idx--;
		len--;
		lenN--;
	}

	if (isRemembered) {
		res.insert(0, "1");
	}
	this->mDigits = res;
	return *this;
}
/**
 * \brief Function do subtraction
 * \details This version of code support "*this" - n with "*this" >= n only
 *			"*this": Minuend
 *          
 * \param n Subtrahend
 * 
 * \return Difference
 */
BigInteger BigInteger::operator-(const BigInteger n) const 
{
	bool isRemembered = false;
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();
	std::string res(len, '0');

	if (n > *this) {
		return BigInteger("0");
	}

	for (int i = 1; i <= len; i++) {
		if (i > (int)n.mDigits.length()) {
			if (isRemembered) {
				res[len - i] = sub(this->mDigits[len - i], '0', isRemembered);
			} else {
				res[len - i] = this->mDigits[len - i];
			}
		} else {
			res[len - i] = sub(this->mDigits[len - i], n.mDigits[lenN - i], isRemembered);
		}
	}

	return BigInteger(res);
}

/**
 * \brief Function do subtraction
 * \details This version of code support "*this" - n with "*this" >= n only
 *			"*this": Minuend
 * 
 * \param n
 * \return 
 */
BigInteger& BigInteger::operator-=(const BigInteger& n)
{
	string res = "";
	bool isRemembered = false;
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();

	if (n > *this) {
		this->mDigits = "0";
		return *this;
	}

	for (int i = 1; i <= len; i++) {
		if (i > (int)n.mDigits.length()) {
			if (isRemembered) {
				this->mDigits[len - i] = sub(this->mDigits[len - i], '0', isRemembered);
			} else {
				this->mDigits[len - i] = this->mDigits[len - i];
			}
		} else {
			this->mDigits[len - i] = sub(this->mDigits[len - i], n.mDigits[lenN - i], isRemembered);
		}
	}
	this->format();
	return *this;//BigInteger(string(res.rbegin(), res.rend()));
}
BigInteger BigInteger::operator&(const BigInteger n) const
{
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();
	int min = MIN(len, lenN);
	string result="";
	for (int i = min; i > 0; i--) {
		result.push_back(AND(this->mDigits.at(len - i), n.mDigits.at(lenN - i)));
	}
	return BigInteger(result);
}

BigInteger BigInteger::operator^(const BigInteger n) const
{
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();
	int max = MAX(len, lenN);
	int min = MIN(len, lenN);
	string result = "";
	if (max != min) {
		for (int i = 0; i < max; i++) {
			if (max - i <= min) {
				int idx = min - max + i;
				result.push_back(len > lenN ? XOR(this->mDigits.at(i), n.mDigits.at(idx)) :
					XOR(this->mDigits.at(idx), n.mDigits.at(i)));
			} else {
				result.push_back(len > lenN ? XOR(this->mDigits.at(i), '0') : XOR(n.mDigits.at(i), '0'));
			}
		}
	}
	else {
		for (int i = 0; i < max; i++) {
			result.push_back(XOR(this->mDigits.at(i), n.mDigits.at(i)));
		}
	}
	return BigInteger(result);
}

/**
 * \brief Function do shift to left n bits
 * \details Current version not support overload bits
 * 
 * \param n Number of bits
 * \return the result
 */
BigInteger BigInteger::operator<<(const int n) const 
{
	if (n > 0) {
		BigInteger result(this->mDigits);
		for (int i = 0; i < n; i++) {
			result.mDigits.push_back('0');
		}
		// return BigInteger(result.mDigits.substr(n));
		return result;
	}

	return BigInteger(this->mDigits);
}

BigInteger BigInteger::operator>>(const int n) const 
{
	if (n > 0) {
		return BigInteger(this->mDigits.substr(0, this->mDigits.length() - n));
	}
	return BigInteger(this->mDigits);
}

bool BigInteger::operator>(const BigInteger n) const 
{
	bool result = false;
	int len = this->mDigits.length();
	int lenN = n.mDigits.length();

	if (len > lenN) {
		result = true;
	} else if (lenN > len) {
		result = false;
	} else {
		for (int i = 0; i < len; i++) {
			if (this->mDigits[i] != n.mDigits[i]) {
				if (this->mDigits[i] == '0') {
					result = false;
				} else {
					result = true;
				}
				break;
			}
		}
	}

	return result;
}

BigInteger BigInteger::operator%(const BigInteger& n) const
{
	int lenN = n.getLen();
	string str(lenN+1, '0');
	str[0] = '1';
	BigInteger mod = modulo(BigInteger(str), n);

	std::vector<BigInteger> g = Split(*this, lenN);
	int N = (int)g.size() - 1;
	while (N > 0) {
		BigInteger T = g[N];
		for (int i = 0; i < lenN; i++) {
			T = T << 1;
			while (T.getLen() > lenN && T.getDigits()[0] == '1') {
				T.Set(0, '0');
				T += mod;
			}
		}
		g[N - 1] +=  T;
		while (g[N - 1].getLen() > lenN && g[N - 1].getDigits()[0] == '1') {
			g[N - 1].Set(0, '0');
			g[N - 1] += mod;
		}
		N = N - 1;
	}

	while (g[0] > n) {
		g[0] = g[0] - n;
	}
	return g[0];
}

BigInteger& BigInteger::operator%=(const BigInteger& n)
{
	int lenN = n.getLen();
	string str(lenN + 1, '0');
	str[0] = '1';
	BigInteger mod = modulo(BigInteger(str), n);

	std::vector<BigInteger> g = Split(*this, lenN);
	int N = (int)g.size() - 1;
	while (N > 0) {
		BigInteger T = g[N];
		for (int i = 0; i < lenN; i++) {
			T = T << 1;
			while (T.getLen() > lenN && T.getDigits()[0] == '1') {
				T.Set(0, '0');
				T += mod;
			}
		}
		g[N - 1] += T;
		while (g[N - 1].getLen() > lenN && g[N - 1].getDigits()[0] == '1') {
			g[N - 1].Set(0, '0');
			g[N - 1] += mod;
		}
		N = N - 1;
	}

	while (g[0] > n) {
		g[0] = g[0] - n;
	}
	this->mDigits = g[0].mDigits;
	return *this;
}

void BigInteger::LShift(int n)
{
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			mDigits.push_back('0');
		}
	}
}

/**
 * \brief This function calculates *this % n
 * \details Current version only supports *this > 0, n > 0
 * 
 * \param n Input n is a BigInteger number
 * 
 * \return Result of *this % n
 */
//BigInteger BigInteger::operator%(const BigInteger n) const
//{
//	BigInteger res;
//	if (*this == BigInteger("0") || n == BigInteger("0") || *this == n) {
//		return res;
//	}
//
//	if (n > *this) {
//		res = *this;
//	} else if (*this > n) {
//		int len = mDigits.length();
//		int lenN = n.mDigits.length();
//		// BigInteger previous(mDigits.substr(len - lenN + 1));
//		BigInteger previous("1");
//		
//		if (mDigits[len - 1] == '1') {
//			res = previous;
//		}
//
//		// res = previous;
//		for (int i = len - 1; i > 0; i--) {
//			// Calculate (previous*2 % n)
//			previous = modulo(previous << 1, n);
//
//			// Calculate res = (res + previous) % n
//			if (mDigits[i - 1] == '1') {
//				res = modulo(res + previous, n);
//			}
//		}
//
//	}
//
//	return res;
//}

bool BigInteger::operator == (const BigInteger n) const 
{
	return mDigits.compare(n.mDigits) == 0;
}

bool BigInteger::operator!=(const BigInteger n) const
{
	return *this == n ? false : true;
}
