#include <iostream>
#include <cstring>
#include <string>
#include "define.h"
#include "algorithm.h"
#include "bigint.h"
struct NUM_INFO{
	char* digits;
	size_t len;
	NUM_INFO(char* _digits, size_t _len) {
		digits = _digits;
		len = _len;
	}
};


NUM_INFO cloneDigits(const char* digs, const size_t len) {
	char* digits = new char[len + 1];
	memcpy(digits, digs, len);
	digits[len] = '\0';
	return NUM_INFO(digits, len);
}

void cloneNumber(BigInt* ptr, const char* digits, const size_t len)
{
	NUM_INFO info = cloneDigits(digits, len);
	ptr->setDigits(info.digits);
	ptr->setLen(info.len);
}

BigInt::BigInt(): mDigits(nullptr), len(0)
{
}

BigInt::BigInt(const int numDigits)
{
	if (numDigits > 0) {
		mDigits = Algorithm::GetInstance()->GenBinaryString(numDigits);
		mDigits[0] = '1';
		len = strlen(mDigits);
	}
	else {
		mDigits = nullptr;
		len = 0;
	}
}

BigInt::~BigInt()
{
	if (mDigits != nullptr) {
		len = 0;
		delete[] mDigits;
		mDigits = nullptr;
	}
}

BigInt::BigInt(const BigInt& bigInt)
{	
	cloneNumber(this, bigInt.mDigits, bigInt.len);
}

BigInt::BigInt(const char* digits)
{
	cloneNumber(this, digits, strlen(digits));
}

vector<BigInt> BigInt::_split(const BigInt& n, const int width) const
{
	int count = 1;
	vector<BigInt> result;
	char* digits = nullptr;
	for (; ;count++) {
		if (count*width >= (int)n.len) {
			break;
		}
	}

	digits = new char[count*width + 1];

	if (count*width > (int)n.len) {
		int size = count*width - (int)n.len;
		memcpy(digits + size, n.mDigits,n.len);
		memset(digits, '0', size);
	} else {
		memcpy(digits, n.mDigits,n.len);
	}

	digits[count*width] = '\0';

	for (int i = count - 1; i >= 0; i--) {
		char* tmp = new char[width + 1];
		memcpy(tmp, digits + i*width, width);
		tmp[width] = '\0';
		result.push_back(BigInt(tmp));
		delete[] tmp;
	}

	delete[] digits;
	return result;
}

void BigInt::_firstComplement(char* digits)
{
	if (digits != nullptr) {
		for (size_t i = 0; i < strlen(digits); i++) {
			digits[i] = digits[i] == '0' ? '1' : '0';
		}
	}
}

/**
 * \brief Function shift left no change bits size
 * 
 * \param bits number of bits to shift
 * \param useFormat Format after shift or not
 */
void BigInt::_shiftLeft(const int bits, const bool useFormat) {
	if (bits > 0 && this->len > 0) {
		char* tmp = this->mDigits;
		char* newDigits = new char[this->len + 1];
		memcpy(newDigits, tmp + bits, len - bits);
		memset(newDigits + (len - bits), '0', bits);
		newDigits[this->len] = '\0';

		cloneNumber(this, newDigits, strlen(newDigits));
		if (useFormat) {
			this->format();
		}

		delete[] tmp;
	}
}

void BigInt::_shiftRight(const int bits, const bool useFormat) {
	if (bits > 0 && this->len > 0) {
		char* tmp = this->mDigits;
		char* newDigits = new char[this->len + 1];
		memcpy(newDigits + bits, tmp, len - bits);
		memset(newDigits, '0', bits);
		newDigits[this->len] = '\0';
		
		cloneNumber(this, newDigits, strlen(newDigits));

		if (useFormat) {
			this->format();
		}

		delete[] tmp;
	}
}

void BigInt::format()
{
	if (this->mDigits != nullptr) {
		char* tmp = this->mDigits;
		int count = 0;
		for (size_t i = 0; i < len; i++) {
			if (this->mDigits[i] != '0') {
				break;
			}
			count++;
		}
		if (count > 0) {
			this->len = this->len - count;
			this->mDigits = new char[this->len + 1];
			memcpy(this->mDigits, tmp + count, this->len + 1);
			this->mDigits[this->len] = '\0';

			delete[] tmp;
		}
	}
}

BigInt BigInt::operator+(const BigInt n)
{
	bool isRemembered = false;
	int len = (int)strlen(mDigits);
	int lenN = (int)strlen(n.mDigits);
	int lenMax = MAX(len, lenN);
	int idx = lenMax - 1;

	len--;
	lenN--;
	char* res = new char[lenMax + 1];
	char c = '0';
	while (len >= 0 || lenN >= 0) {
		char a = len >= 0 ? mDigits[len] : '0';
		char b = lenN >= 0 ? n.mDigits[lenN] : '0';
		res[idx] = ((a^b)^c);
		c = (a & b) | (a & c) | (b & c);
		idx--;
		len--;
		lenN--;
	}

	res[lenMax] = '\0';
	BigInt result;
	if (c == '1') {
		result.mDigits = new char[lenMax + 2];
		memcpy(result.mDigits + 1, res, lenMax);
		result.mDigits[lenMax + 1] = '\0';
		result.len = lenMax + 1;
		result.mDigits[0] = '1';
		delete[] res;
	} else {
		result.mDigits = new char[lenMax + 1];
		memcpy(result.mDigits, res, lenMax);
		result.mDigits[lenMax] = '\0';
		result.len = lenMax;
		delete[] res;
	}
	return result;
}

void BigInt::operator+=(const BigInt& n)
{
	bool isRemembered = false;
	int len = (int)strlen(mDigits);
	int lenN = (int)strlen(n.mDigits);
	size_t lenMax = MAX(len, lenN);
	int idx = (int)(lenMax - 1);

	len--;
	lenN--;
	char* res = new char[lenMax + 1];
	char c = '0';
	while (len >= 0 || lenN >= 0) {
		char a = len >= 0 ? mDigits[len] : '0';
		char b = lenN >= 0 ? n.mDigits[lenN] : '0';
		res[idx] = ((a^b)^c);
		c = (a & b) | (a & c) | (b & c);
		idx--;
		len--;
		lenN--;
	}

	res[lenMax] = '\0';
	if (c == '1') {
		char* tmp = this->mDigits;
		this->mDigits = new char[lenMax + 2];
		this->len = lenMax + 1;
		memcpy(this->mDigits + 1, res, lenMax);
		this->mDigits[lenMax + 1] = '\0';
		this->mDigits[0] = '1';
		delete[] tmp;
		delete[] res;
	} else {
		char* tmp = this->mDigits;
		this->mDigits = new char[lenMax + 1];
		this->mDigits[lenMax] = '\0';
		this->len = lenMax;
		memcpy(this->mDigits, res, lenMax);
		delete[] tmp;
		delete[] res;
	}
}

void BigInt::operator=(const BigInt& n)
{
	if (this->mDigits != nullptr) {
		delete[] this->mDigits;
	}

	this->mDigits = new char[n.len + 1];
	memcpy(this->mDigits, n.mDigits, n.len);
	this->len = n.len;
	this->mDigits[this->len] = '\0';
}

bool BigInt::operator>(const BigInt& n)
{
	bool result = false;
	size_t len = this->len;
	size_t lenN = n.len;

	if (len > lenN) {
		result = true;
	} else if (len < lenN) {
		result = false;
	} else {
		for (size_t i = 0; i < len; i++) {
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

bool BigInt::operator==(const BigInt& n) const
{
	bool result = true;
	size_t len = this->len;
	size_t lenN = n.len;

	if (len != lenN) {
		result = false;
	} else {
		for (size_t i = 0; i < len; i++) {
			if (this->mDigits[i] != n.mDigits[i]) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool BigInt::operator>=(const BigInt& n)
{
	return *this > n || *this == n;
}

BigInt BigInt::operator%(const BigInt& n) const
{
	// Calculate 2^Width(Y) mod Y
	size_t lenN = n.len;
	char* modChars = new char[lenN + 2];
	memset(modChars, '0', lenN + 2);
	modChars[0] = '1';
	modChars[lenN + 1] = '\0';
	BigInt mod = BigInt(modChars) - n;
	delete[] modChars;

	auto _shiftLeftOne = [](BigInt* num) -> void {
		if (num->mDigits[0] == '0') {
			num->_shiftLeft(1, false);
		} else {
			char* tmp = new char[num->len + 2];
			memcpy(tmp, num->mDigits, num->len);
			tmp[num->len] = '0';
			tmp[num->len + 1] = '\0';
			delete[] num->mDigits;
			num->mDigits = tmp;
			num->len = num->len + 1;
		}
	};

	vector<BigInt> g = _split(*this, lenN);

	int N = (int)g.size() - 1;
	while (N > 0) {
		BigInt T = g[N];
		for (size_t i = 0; i < lenN; i++) {
			_shiftLeftOne(&T);
			while (T.len > lenN && T.mDigits[0] == '1') {
				T.mDigits[0] = '0';
				T += mod;
			}

			T.format();
		}
		g[N - 1] +=  T;

		while (g[N-1].len > lenN && g[N - 1].mDigits[0] == '1') {
			g[N - 1].mDigits[0] = '0';
			g[N - 1] += mod;
		}
		N = N - 1;
	}

	g[0].format();	
	while (g[0] >= n) {
		g[0] = g[0] - n;
	}

	if (g[0].len == 0 ) {
		return BigInt("0");
	}
	return g[0];
}

/**
 * \brief Function calculate a - b
 * \details This version for only a >= b
 * 
 * \param n The number b
 * \return a - b
 */
BigInt BigInt::operator-(const BigInt& n)
{
	char* digits = new char[n.len + 1];
	memcpy(digits, n.mDigits, n.len);
	digits[n.len] = '\0';

	_firstComplement(digits);

	if (this->len > n.len) {
		char* tmp = digits;
		digits = new char[this->len + 1];
		memset(digits, '1', this->len);
		memcpy(digits + (this->len - n.len), tmp, n.len);
		digits[this->len] = '\0';
		delete[] tmp;
	}

	BigInt com = BigInt(digits) + BigInt("1");

	BigInt res = *this + com;

	if (res.len > this->len) {
		char* tmp = res.mDigits;
		res.mDigits = new char[this->len + 1];
		memcpy(res.mDigits, tmp + (res.len - this->len), this->len);
		res.mDigits[this->len] = '\0';
		res.len = this->len;
		res.format();

		delete[] tmp;
	}

	delete[] digits;
	return res;
}

BigInt BigInt::operator>>(const int bits)
{
	if (this->len == 0 || this->mDigits == nullptr) {
		return BigInt(this->mDigits);
	}
	BigInt res(this->mDigits);
	res._shiftRight(bits);
	return res;
}

BigInt BigInt::operator<<(const int bits)
{
	BigInt res(this->mDigits);
	char* tmp = new char[this->len + bits + 1];
	memcpy(tmp, this->mDigits, this->len);
	memset(tmp + this->len, '0', bits);
	tmp[this->len + bits] = '\0';
	
	delete[] res.mDigits;
	res.mDigits = tmp;
	res.len = this->len + bits;
	res.format();
	return res;
}
