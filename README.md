# RSA Implementation

This the RSA 2048 bits implementation using C++ with [Boost::multiprecision](https://www.boost.org/doc/libs/1_72_0/libs/multiprecision/doc/html/index.html).

## Table of content
- [Basic setup](#basic-setup)
    - [Big number data type](#big-number-data-type)
    - [Mod calculation](#mod-calculation)
    - [MulMod calculation](#mulmod-calculation)
    - [PowMod calculation](#powmod-calculation)
    - [Primes test](#primes-test)

- [RSA calculations](#rsa-calculations)
	- [Generate strong primes](#generate-strong-primes)
	- [Find e and d](#find-e-and-d)
	- [Fast decryption using CRT](#fast-decryption-using-crt)
- [References](#references)

## Basic setup

RSA does things with primes which are integer numbers. To increase the security of the system, one easy step we can do is increase the size of an integer. For RSA 2048 bits, `p,q` are 1024 bits integers then `p*q` is nearly 2048 bits. The most important thing is how to represent a very large integer like 1024 or 2048 bits. The first way we can think about is to write a BigInt class, with C++, we can overload operators like +, -, \*, /, etc. The second way is easier, this is also the way this repo implemented, that is using a library. The library used here is Boost. The next session will show how to represent a very big number by Boost::multiprecision. To install Boost library, follow this [tutorial for Windows](https://https://tomkoos.github.io/cpp/boost-vs.html) or [tutorial for Linux](https://onethinglab.com/2019/01/30/how-to-install-latest-boost-library-on-ubuntu/).

### Big number data type
Using this code to define a new data type for big number.
````C++
namespace mp = boost::multiprecision;
typedef mp::number<mp::cpp_int_backend<4096, 4096, mp::signed_magnitude, mp::unchecked, void> >  number_t; // int4096_t
````
From now, we can use the data type **number_t** for 4096 bits numbers. (***Note:*** *There is a space before close angle brackets* `>`).
### Mod calculation
### MulMod calculation
### PowMod calculation
### Primes test
## RSA calculations
### Generate strong primes
### Find e and d
### Fast decryption using CRT
## References
