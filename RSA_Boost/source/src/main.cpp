#include "utils.h"
#include "algorithm.h"

using namespace std;

void main_calculation()
{
	int bits = 1024;
	std::chrono::steady_clock::time_point begin, end;
	Algorithm* algorithm = Algorithm::GetInstance();
	number_t a = algorithm->GenerateNumber(bits);
	sleepcp(1000);
	number_t b = algorithm->GenerateNumber(bits);

	sleepcp(1000);
	number_t c = algorithm->GenerateNumber(bits);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;


	begin = std::chrono::steady_clock::now();
	number_t sum = a + b;
	end = std::chrono::steady_clock::now();
	cout << "sum = " << sum << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t d = algorithm->MulMod(a, b, c);
	end = std::chrono::steady_clock::now();
	cout << "d = " << d << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t e = algorithm->PowMod(a, b, c);
	end = std::chrono::steady_clock::now();
	cout << "e = " << e << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
}

string toBinary(const number_t& n)
{
    string r;
    number_t tmp = n;
    while(tmp != 0)
    {
        r = (tmp % 2 == 0 ? "0":"1") + r;
        tmp /= 2;
    }
    return r;
}

number_t CrtDecrypt(const number_t& c, const number_t& d, const number_t& n, const number_t& p, const number_t& q)
{
	cout << "CRT Decrypt================!\n";
	Algorithm* algorithm = Algorithm::GetInstance();
	number_t dp = d % (p - 1);
	number_t dq = d % (q - 1);
	number_t v, y, g;
	algorithm->AlgBinaryBezout(p, q, v, y, g);

	cout << "v = " << v << endl;
	cout << "y = " << y << endl;

	number_t res = algorithm->PowMod(c, dp, n) + algorithm->MulMod(algorithm->MulMod(p, v, n), (algorithm->PowMod(c, dq, n) - algorithm->PowMod(c, dp, n)), n);

	cout << "End CRT Decrypt=============!\n";
	return res % n;
}

void main_rsa()
{
	Algorithm* algorithm = Algorithm::GetInstance();
	std::chrono::steady_clock::time_point begin, end;

	number_t p = algorithm->GenPrime(512);
	sleepcp(1000);
	number_t q = algorithm->GenPrime(512);

	number_t n = p * q;
	number_t phi = (p - 1)*(q - 1);
	number_t e{"65537"};



	cout<< "p = "<< p <<endl;
	cout<< "q = "<< q <<endl;
	cout<< "n = "<< n <<endl;
	cout<< "phi = "<< phi <<endl;


	number_t d, tmp, g;
	algorithm->AlgBinaryBezout(e, phi, d, tmp, g);
	cout << "GCD: " << g << endl;
	cout << "d: " << d << endl;
	cout << "tmp: " << tmp << endl;

	number_t inv = algorithm->GetEInverse(e, phi);
	cout << "inv: " << inv << endl;

	number_t m = algorithm->GenerateNumber(1000);

	cout << "M : " << m << endl;
	cout<<"M : "<<toBinary(m)<<endl;

	begin = std::chrono::steady_clock::now();
	number_t enc = algorithm->PowMod(m, e, n);
	end = std::chrono::steady_clock::now();
	cout << "Crypt : " << enc << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t dec = algorithm->PowMod(enc, d, n);
	end = std::chrono::steady_clock::now();
	cout << "Decrypt : " << dec << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t dec1 = CrtDecrypt(enc, d, n, p, q);
	end = std::chrono::steady_clock::now();
	cout << "Decrypt1 : " << dec1 << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
}

int main()
{
	//main_calculation();

	//main_rsa();
	std::chrono::steady_clock::time_point begin, end;
	
	begin = std::chrono::steady_clock::now();
	number_t p = Algorithm::GetInstance()->GenStrongPrime(512);
	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	return 1;
}