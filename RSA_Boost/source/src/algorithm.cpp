#include "utils.h"
#include "algorithm.h"

using namespace std;

Algorithm* Algorithm::mInstance = nullptr;

void Algorithm::genKey(const number_t& p, const number_t& q, const number_t& phi, const number_t& n, number_t& e, number_t& d)
{
	number_t t{ "10922" }, tmp, g; // 6t+5 = 65537

	while (1) {
		e = 6 * t + 1;
		if (isPrime(e)) {
			AlgBinaryBezout(e, phi, d, tmp, g);
			if (d * d >= n) {
				break;
			}
		}

		e = 6 * t + 5;
		if (isPrime(e)) {
			AlgBinaryBezout(e, phi, d, tmp, g);
			if (d * d >= n) {
				break;
			}
		}
		t += 1;
	}
}

Algorithm* Algorithm::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new Algorithm();
	}
	return mInstance;
}

std::string Algorithm::NumberToBinary(const number_t& num)
{
	std::string r;
	number_t n = num;
	while (n != 0) {
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	return r;
}

number_t Algorithm::BinaryToNumber(const std::string str)
{
	return binaryToDecimal(str);
}

number_t Algorithm::binaryToDecimal(string n)
{
	string num = n;
	number_t dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	number_t base = 1;

	int len = num.length();
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}

	return dec_value;
}

string Algorithm::GenBinaryString(int length)
{
	srand((unsigned int)time(nullptr));
	auto randchar = []() -> char {
		const char charset[] = "01";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};

	string str(length, 0);
	generate_n(str.begin(), length, randchar);

	str[0] = '1';
	return str;
}

number_t Algorithm::GenerateNumber(int length)
{
	return binaryToDecimal(GenBinaryString(length));
}

number_t Algorithm::MulMod(const number_t& x, const number_t& y, const number_t& n)
{
	if (x == 0 || y == 0 || n <= 0) {
		return 0;
	}

	/*number_t X = x;
	number_t Y = y;
	number_t res = 0;

	if (y % 2 == 1) {
		res = X;
	}

	Y >>= 1;
	while( Y > 0) {
		X <<= 1;

		if (Y % 2 == 1) {
			res += X;
		}

		Y >>= 1;
	}
	return res % n;*/

	number_t mul = x * y;

	return mul % n;
}

number_t Algorithm::PowMod(const number_t& x, const number_t& p, const number_t& n)
{
	if (x == 0 || n <= 0 || p < 0) {
		return 0;
	} else if (p == 0) {
		return 1 % n;
	}

	number_t znX = x % n, res = 1, tmp = p;

	if (p % 2 == 1) {
		res = znX;
	}

	tmp >>= 1;
	while (tmp > 0) {
		znX = MulMod(znX, znX, n);

		if (tmp % 2 == 1) {
			res = MulMod(res, znX, n);
		}

		tmp >>= 1;
	}
	return res;
}

#include <chrono>

bool Algorithm::isPrime(number_t n) {
	vector<number_t> bases{ 2, 5, 7, 9 };
	for (int i = 0; i < (int)bases.size(); i++) {

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		number_t res = PowMod(bases[i], n - 1, n);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		 LOG("powMod: " << res << "\n\t" << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << MICRO_S);

		if (res != 1) {
			return false;
		}
	}
	return true;
}

number_t Algorithm::GenPrime(const int length)
{
	std::chrono::steady_clock::time_point begin, end;
	
	number_t prime, tmp = GenerateNumber(length - 3);

	begin = std::chrono::steady_clock::now();
	while (true) {

		prime = 6*tmp + 1;
		if (isPrime(prime)) {
			LOG("Prime (6n + 1)!!!!!");
			break;
		}

		prime = 6*tmp + 5;
		if (isPrime(prime)) {
			LOG("Prime (6n + 5)!!!!!");
			break;
		}

		tmp += 1;
	}

	end = std::chrono::steady_clock::now();
	LOG("Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]");
	LOG("Prime is: " << prime);
	return prime;
}

number_t Algorithm::GenStrongPrime(const int length)
{

	// METHOD 1: i*p + 1

	number_t r = GenPrime(length), p, i = 2;
	bool found = false;
	while (!found) {
		LOG("i = " << i << " .... ");
		p = i * r + 1;

		if (isPrime(p)) {
			found = true;
		}

		i <<= 1;
	}
	LOG("R = " << r << "; P = " << p << "; i = " << i);
	return p;
}

number_t Algorithm::GetInverse(const number_t& e, const number_t& phi)
{
	number_t a = e, b = phi;
	number_t b0 = b, t, q;
	number_t x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

number_t Algorithm::GetEInverse(const number_t& e, const number_t& phi)
{
	number_t mod = phi % e;
	number_t  k = 0, total = 1;

	while (total != 0) {
		k = k + 1;
		total = (total + mod) % e;
	}
	return (k * phi + 1) / e;
}

number_t Algorithm::SolveCrt(const std::vector<number_t> lstN, const std::vector<number_t> lstA)
{
	int i, len = (int)lstN.size();
	number_t p, prod = 1, sum = 0;
 
	for (i = 0; i < len; i++) prod *= lstN[i];
 
	for (i = 0; i < len; i++) {
		p = prod / lstN[i];
		number_t inv = GetInverse(p, lstN[i]);
		sum += lstA[i] * inv * p;
	}

	return sum % prod;
}

void Algorithm::AlgBinaryBezout(const number_t& a, const number_t& b, number_t& x, number_t& y, number_t& g)
{
	g = 1;
	number_t ta = a, tb = b, u = a, v = b, A = 1, B = 0, C = 0, D = 1;
	while (ta % 2 == 0 && tb % 2 == 0) {
		ta >>= 1;
		tb >> 1;
		g <<= 1;
	}

	while (u > 0) {
		while (u % 2 == 0) {
			u >>= 1;
			if (A % 2 == 0 && B % 2 == 0) {
				A >>= 1;
				B >>= 1;
			} else {
				A = (A + b) / 2;
				B = (B - a) / 2;
			}
		}
		while (v % 2 == 0) {
			v >>= 1;
			if (C % 2 == 0 && D % 2 == 0) {
				C >>= 1;
				D >>= 1;
			} else {
				C = (C + b) / 2;
				D = (D - a) / 2;
			}
		}
		if (u >= v) {
			u = u - v;
			A = A - C;
			B = B - D;
		} else {
			v = v - u;
			C = C - A;
			D = D - B;
		}
	}
	x = C;
	y = D;
	g = g * v;
}

number_t Algorithm::RsaDecryptCrt(const number_t& c, const number_t& d, const number_t& n, const number_t& p, const number_t& q)
{
	number_t dp = d % (p - 1);
	number_t dq = d % (q - 1);
	std::vector<number_t> lstN{p, q};
	std::vector<number_t> lstA{PowMod(c, dp, p), PowMod(c, dq, q)};

	number_t res = SolveCrt(lstN, lstA);

	return res % n;
}

RSA_INFO Algorithm::RsaGenKey(const int len)
{
	std::chrono::steady_clock::time_point begin, end;
	number_t p = GenPrime(len);
	sleepcp(1000);
	number_t q = GenPrime(len);

	LOG_TIME(begin);
	number_t n = p * q;
	LOG_TIME(end);
	LOG("Calculated n = q*q "<< TIME_DIFF(end,begin) << MICRO_S);

	LOG_TIME(begin);
	number_t phi = (p - 1)*(q - 1);
	LOG_TIME(end);
	LOG("Calculated phi = (q-1)*(q-1) " << TIME_DIFF(end, begin) << MICRO_S);

	/*number_t e{"65537"}, d, tmp, g;
	AlgBinaryBezout(e, phi, d, tmp, g);*/

	number_t e, d;

	LOG_TIME(begin);
	genKey(p, q, phi, n, e, d);
	LOG_TIME(end);
	LOG("Generated e, d" << TIME_DIFF(end, begin) << MICRO_S);

	return RSA_INFO(p, q, n, phi, e, d);
}

number_t Algorithm::RsaEncrypt(const number_t& m, const number_t& e, number_t& n)
{
	return PowMod(m, e, n);
}

number_t Algorithm::RsaDecrypt(const number_t& c, const RSA_INFO& info)
{
	return RsaDecryptCrt(c, info.d, info.n, info.p, info.q);
}

void Algorithm::RsaGenED(const number_t& p, const number_t& q, const number_t& phi, const number_t& n, number_t& e, number_t& d)
{
	genKey(p, q, phi, n, e, d);
}
