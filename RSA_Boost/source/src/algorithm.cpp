#include "algorithm.h"

using namespace std;

Algorithm* Algorithm::mInstance = nullptr;

Algorithm* Algorithm::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new Algorithm();
	}
	return mInstance;
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
		 cout << "   RES: " << res << endl;
		 std::cout << "   Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

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
			cout<<"Prime (6n + 1)!!!!!"<<endl;
			break;
		}

		prime = 6*tmp + 5;
		if (isPrime(prime)) {
			cout<<"Prime (6n + 5)!!!!!"<<endl;
			break;
		}

		tmp += 2;
	}

	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

	cout << "Prime is: " << prime << endl;
	return prime;
}

number_t Algorithm::GenStrongPrime(const int length)
{
	number_t r = GenPrime(length), p, i = 2;
	bool found = false;
	while (!found) {
		cout << "i = " << i << "....\n";
		p = i * r + 1;

		if (isPrime(p)) {
			found = true;
		}

		i <<= 1;
	}
	cout << "R = " << r << "; P = " << p << "; i = " << i << endl;
	return p;
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
