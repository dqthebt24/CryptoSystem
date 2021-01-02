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

void main_rsa(bool isBinaryFormat = true, number_t p = 0, number_t q = 0)
{
	chrono::steady_clock::time_point begin, end;
	Algorithm* alg = Algorithm::GetInstance();
	RSA_INFO info;

	if (p == 0) { // Generate new primes
		cout << "RSA Gen Keys started!!!\n" << endl;
		begin = std::chrono::steady_clock::now();
		info = alg->RsaGenKey(1024);
		end = chrono::steady_clock::now();
		cout << "RSA Gen Keys done!!!" << chrono::duration_cast<chrono::microseconds>(end - begin).count() << MICRO_S << endl;
	} else {
		info.p = p;
		info.q = q;

		begin = chrono::steady_clock::now();
		info.n = info.p * info.q;
		end = chrono::steady_clock::now();
		cout << "Calculated n = p*q " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << MICRO_S << endl;

		begin = chrono::steady_clock::now();
		info.phi = (info.p - 1) * (info.q - 1);
		end = chrono::steady_clock::now();
		cout << "Calculated phi = (p - 1)*(q - 1) " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << MICRO_S << endl;
		
		begin = std::chrono::steady_clock::now();
		alg->RsaGenED(info.p, info.q, info.phi, info.n, info.e, info.d);
		end = chrono::steady_clock::now();
		cout << "Generated e, d " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << MICRO_S << endl;
		
	}

	if (isBinaryFormat) {
		cout << "p = " << alg->NumberToBinary(info.p) << endl;
		cout << "q = " << alg->NumberToBinary(info.q) << endl;
		cout << "n = " << alg->NumberToBinary(info.n) << endl;
		cout << "phi = " << alg->NumberToBinary(info.phi) << endl;
		cout << "e = " << alg->NumberToBinary(info.e) << endl;
		cout << "d = " << alg->NumberToBinary(info.d) << endl;
	} else {
		cout << "p = " << info.p << endl;
		cout << "q = " << info.q << endl;
		cout << "n = " << info.n << endl;
		cout << "phi = " << info.phi << endl;
		cout << "e = " << info.e << endl;
		cout << "d = " << info.d << endl;
	}

	number_t m = alg->GenerateNumber(512);

	if (isBinaryFormat) {
		cout << "M: " << alg->NumberToBinary(m) << endl;
	} else {
		cout << "M: " << m << endl;
	}
	

	begin = chrono::steady_clock::now();
	number_t c = alg->RsaEncrypt(m, info.e, info.n);
	end = chrono::steady_clock::now();

	if (isBinaryFormat) {
		cout << "Encrypted: " << alg->NumberToBinary(c) << endl;
	} else {
		cout << "Encrypted: " << c << endl;
	}
	cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << MICRO_S << endl;

	begin = chrono::steady_clock::now();
	number_t dec = alg->RsaDecrypt(c, info);
	end = chrono::steady_clock::now();
	if (isBinaryFormat) {
		cout << "Decrypted: " << alg->NumberToBinary(dec) << endl;
	} else {
		cout << "Decrypted: " << dec << endl;
	}
	cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << MICRO_S << endl;
}
int main(int argc, char* argv[])
{
	Algorithm* alg = Algorithm::GetInstance();
	// main_calculation();

	//main_cmp();

	if (argc >= 3) {
		main_rsa(false, alg->BinaryToNumber(string(argv[1])), alg->BinaryToNumber(string(argv[2])));
	} else {
		main_rsa();
	}

	return 1;
}