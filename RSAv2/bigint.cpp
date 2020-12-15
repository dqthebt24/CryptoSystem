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
		// [DB] printf("THIS0000: %x;;;%x\n",this, this->mDigits);
	}
	else {
		mDigits = nullptr;
		len = 0;
	}
}

BigInt::~BigInt()
{
	// cout << "~~~~~~~~~~~~" << endl;
	if (mDigits != nullptr) {
		// cout << "Delete!!!!!" << endl;
		len = 0;
		// [DB] printf("DEL: %x\n", mDigits);
		delete[] mDigits;
		mDigits = nullptr;
	}
}

BigInt::BigInt(const BigInt& bigInt)
{	
	cloneNumber(this, bigInt.mDigits, bigInt.len);
	// [DB] printf("AAAAA:%x\n", this->mDigits);
}

BigInt::BigInt(const char* digits)
{
	cloneNumber(this, digits, strlen(digits));
}

vector<BigInt> BigInt::_split(const BigInt& n, const int width)
{
	vector<BigInt> result;
	string str(n.mDigits);
	int len = str.length();
	int i = 1;
	for (; i*width <= len; i++) {
		result.push_back(BigInt(str.substr(len - i*width, width).c_str()));
	}

	if ((i - 1) * width < len) {
		result.push_back(BigInt(str.substr(0, (len - (i - 1) * width)).c_str()));
	}

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

void BigInt::_shiftLeft(const int bits) {
	if (bits > 0) {
		char* tmp = this->mDigits;
		char* newDigits = new char[this->len + 1];
		memcpy(newDigits, tmp + bits, len - bits);
		memset(newDigits + (len - bits), '0', bits);
		newDigits[this->len] = '\0';

		cloneNumber(this, newDigits, strlen(newDigits));
		this->format();

		delete[] tmp;
	}
}

void BigInt::_shiftRight(const int bits) {
	if (bits > 0) {
		char* tmp = this->mDigits;
		char* newDigits = new char[this->len + 1];
		memcpy(newDigits + bits, tmp, len - bits);
		memset(newDigits, '0', bits);
		newDigits[this->len] = '\0';
		
		cloneNumber(this, newDigits, strlen(newDigits));

		this->format();

		delete[] tmp;
	}
}

void BigInt::format()
{
	if (this->mDigits != nullptr) {
		char* tmp = this->mDigits;
		int count = 0;
		for (int i = 0; i < len; i++) {
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
	size_t lenMax = MAX(len, lenN);
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

	this->mDigits = new char[n.len];
	memcpy(this->mDigits, n.mDigits, n.len);
	this->len = len;
	this->mDigits[len] = '\0';
}

bool BigInt::operator>(const BigInt& n)
{
	bool result = false;
	size_t len = this->len;
	size_t lenN = n.len;

	cout<<"LEN: "<<len<<"<>"<<lenN;
	if (len > lenN) {
		result = true;
		cout<<"RES1111\n";
	} else if (len < lenN) {
		result = false;
		cout<<"RES22222\n";
	} else {
		for (size_t i = 0; i < len; i++) {
			if (this->mDigits[i] != n.mDigits[i]) {
				if (this->mDigits[i] == '0') {
					result = false;
					cout<<"RES33333\n";
				} else {
					result = true;
					cout<<"RES44444\n";
				}
				break;
			}
		}
	}
	return result;
}

bool BigInt::operator==(const BigInt& n)
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

BigInt BigInt::operator%(const BigInt& n)
{
	cout<<"N= "<<n.mDigits<<endl;
	// Calculate 2^Width(Y) mod Y
	int lenN = (int)n.len;
	char* modChars = new char[lenN + 2];
    memset(modChars, '0', lenN + 2);
    modChars[0] = '1';
    modChars[lenN + 1] = '\0';
	BigInt mod = BigInt(modChars) - n;
	delete[] modChars;

	vector<BigInt> g = _split(*this, lenN);
	int N = (int)g.size() - 1;
	cout<<"N="<<N<<endl;
	cout<<g[0].mDigits<<endl;
	while (N > 0) {
		BigInt T = g[N];
		for (int i = 0; i < lenN; i++) {
			T = T << 1;
			while (T.len > lenN && T.mDigits[0] == '1') {
				T.mDigits[0] = '0';
				T += mod;
			}
		}
		g[N - 1] +=  T;
		while (g[N - 1].len > lenN && g[N - 1].mDigits[0] == '1') {
			g[N - 1].mDigits[0] = '0';
			g[N - 1] += mod;
		}
		N = N - 1;
	}


	while (g[0] > n) {
		BigInt tmp = BigInt(g[0].mDigits) - n;
		g[0] = tmp;
		cout<<"TMP: "<<tmp.mDigits<<endl;
		cout<<"COMPARE: "<<(tmp > n)<<endl;
		cout<<"G0: "<<g[0].mDigits<<endl;
	}

	cout<<"G0FFF: "<<(g[0].mDigits)<<endl;
	return g[0];
}

BigInt BigInt::operator-(const BigInt& n)
{
	char* digits = new char[n.len];
	memcpy(digits, n.mDigits, n.len);
	digits[n.len] = '\0';

	_firstComplement(digits);
	BigInt com = BigInt(digits) + BigInt("1");
	BigInt res = *this + com;
	if (res.len > this->len) {
		char* tmp = res.mDigits;
		res.mDigits = new char[this->len];
		memcpy(res.mDigits, tmp + (res.len - this->len), this->len);
		res.mDigits[this->len - 1] = '\0';
		res.format();

		delete[] tmp;
	}

	return res;
}

BigInt BigInt::operator>>(const int bits)
{
	BigInt res(this->mDigits);
	res._shiftRight(bits);
	return res;
}

BigInt BigInt::operator<<(const int bits)
{
	BigInt res(this->mDigits);
	res._shiftLeft(bits);
	return res;
}
