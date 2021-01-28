# RSA Implementation

This the RSA 2048 bits implementation using C++ with [Boost::multiprecision](https://www.boost.org/doc/libs/1_72_0/libs/multiprecision/doc/html/index.html).

## Table of content
- [Basic setup](#basic-setup)
    - [Big number data type](#big-number-data-type)
    - [MulMod calculation](#mulmod-calculation)
    - [PowMod calculation](#powmod-calculation)
    - [Primes test](#primes-test)

- [RSA calculations](#rsa-calculations)
	- [Generate strong primes](#generate-strong-primes)
	- [Find e and d](#find-e-and-d)
	- [Fast decryption using CRT](#fast-decryption-using-crt)
- [References](#references)

## Basic setup

The library used here is Boost. The next session will show how to represent a very big number by Boost::multiprecision. To install Boost library, follow this [tutorial for Windows](https://https://tomkoos.github.io/cpp/boost-vs.html) or [tutorial for Linux](https://onethinglab.com/2019/01/30/how-to-install-latest-boost-library-on-ubuntu/).

### Big number data type
Using this code to define a new data type for big number.
````C++
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;
typedef mp::number<mp::cpp_int_backend<4096, 4096, mp::signed_magnitude, mp::unchecked, void> >  number_t; // int4096_t
````
From now, we can use the data type **number_t** for 4096 bits numbers.

(***Note:*** *There is a space before close angle brackets* `>`).
### MulMod calculation
**MulMod** is giving 3 numbers *a, b, n* then caculate ![mulmod](https://latex.codecogs.com/gif.latex?a*b%25n).

For RSA only 2048 bits with the **number_t** above, we can do **MulMod** by doing **multiply** first then doing **modulo**. Because for *a,b* 1024 bits then ![amulb](https://latex.codecogs.com/gif.latex?a*b) is at most 2048 bits when **number_t** can be used for 4096 bits number. Below is **MulMod** algorithm.

<p align="center">
  <img alt="drawing" width="250" height="140" src="./Images/mulmod_alg.jpg" />
</p>


### PowMod calculation
**MulMod** is giving 3 numbers *a, b, n* then caculate ![powmod](https://latex.codecogs.com/gif.latex?a%5Eb%25n).
Do **MulMod** using below algorithm.

<p align="center">
  <img alt="drawing" width="550" height="320" src="./Images/powmod_alg.jpg" />
</p>

### Primes test
Using [Fermat little theorem](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem) and [Pseudo prime](https://en.wikipedia.org/wiki/Pseudoprime), create algorithm to check a pseudo prime with some bases `{2,5,7,9}`. The algorithm is below

<p align="center">
  <img alt="drawing" width="350" height="180" src="./Images/check_prime.jpg" />
</p>

*Note:* ***Carmichael numbers*** *are composite numbers that satisfies the Fermat’s little theorem. But we also can use Fermat’s little theorem to check primes because the probability that `n` is a Carmichael numbers is very small. The first 3 Carmichael numbers are* ***561***, ***1105*** *and* ***1729***.

## RSA calculations
### Generate strong primes
### Find e and d
### Fast decryption using CRT
## References

