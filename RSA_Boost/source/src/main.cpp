#include <vector>

#include "define.h"
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

void main_cmp()
{
	Algorithm* algorithm = Algorithm::GetInstance();
	std::chrono::steady_clock::time_point begin, end;

	number_t p = algorithm->GenPrime(1024);
	sleepcp(1000);
	number_t q = algorithm->GenPrime(1024);

	number_t n = p * q;
	number_t phi = (p - 1)*(q - 1);
	number_t e{"65537"};



	cout<< "p = "<< p <<endl;
	cout<< "q = "<< q <<endl;
	cout<< "n = "<< n <<endl;
	cout<< "phi = "<< phi <<endl;


	number_t d, tmp, g;
	begin = std::chrono::steady_clock::now();
	algorithm->AlgBinaryBezout(e, phi, d, tmp, g);
	end = std::chrono::steady_clock::now();
	cout << "GCD: " << g << endl;
	cout << "d: " << d << endl;
	cout << "d^4 > n: " << (d*d*d*d > n) << endl;
	cout << "tmp: " << tmp << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t inv1 = algorithm->GetEInverse(e, phi);
	end = std::chrono::steady_clock::now();
	cout << "Inv1 : " << inv1 << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t inv2 = algorithm->GetInverse(e, phi);
	end = std::chrono::steady_clock::now();
	cout << "Inv2 : " << inv2 << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;

	number_t m = algorithm->GenerateNumber(1000);

	cout << "M : " << m << endl;
	cout<<"M : "<<NumToBinary(m)<<endl;

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
	number_t dec1 = algorithm->RsaDecryptCrt(enc, d, n, p, q);
	end = std::chrono::steady_clock::now();
	cout << "Decrypt1 : " << dec1 << endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[탎]" << std::endl;
}

void main_rsa()
{
	std::chrono::steady_clock::time_point begin, end;
	begin = std::chrono::steady_clock::now();
	RSA_INFO info = Algorithm::GetInstance()->RsaGenKey(1024);
	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << MICRO_S << std::endl;

	std::cout << "p = " << info.p << std::endl;
	std::cout << "q = " << info.q << std::endl;
	std::cout << "n = " << info.n << std::endl;
	std::cout << "phi = " << info.phi << std::endl;
	std::cout << "e = " << info.e << std::endl;
	std::cout << "d = " << info.d << std::endl;

	number_t m = Algorithm::GetInstance()->GenerateNumber(512);
	std::cout << "M: " << m << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t c = Algorithm::GetInstance()->RsaEncrypt(m, info.e, info.n);
	end = std::chrono::steady_clock::now();
	std::cout << "Encrypted: " << c << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << MICRO_S << std::endl;

	begin = std::chrono::steady_clock::now();
	number_t dec = Algorithm::GetInstance()->RsaDecrypt(m, info);
	end = std::chrono::steady_clock::now();
	std::cout << "Decrypted: " << dec << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << MICRO_S << std::endl;
}
int main()
{
	// main_calculation();

	//main_cmp();

	main_rsa();

	return 1;
}