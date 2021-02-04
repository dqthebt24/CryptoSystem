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
Do **MulMod** using below algorithm(from \[[1](#ref1)\]).

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
The steps of RSA calculations are:

![](https://latex.codecogs.com/gif.latex?1.%5C%20Choose%5C%202%5C%20big%5C%20primes%5C%20p%2Cq)

![](https://latex.codecogs.com/gif.latex?2.%5C%20Calculate%5C%20n%5C%20%3D%5C%20pq%2C%5C%20%5Cphi%5C%20%3D%5C%20%28p-1%29%28q-1%29)

![](https://latex.codecogs.com/gif.latex?3.%5C%20Choose%5C%20e%5Cin%20%5B2%2C%5Cphi-1%5D%5C%20satifies%5C%20gcd%28e%2C%5Cphi%29%3D1)

![](https://latex.codecogs.com/gif.latex?4.%5C%20Find%5C%20d%5Cin%20%5B2%2C%5Cphi-1%5D%5C%20satifies%5C%20ed%5Cequiv%5C%201%5C%20%5Bmod%5C%20%5Cphi%5D)

![](https://latex.codecogs.com/gif.latex?5.%5C%20Public%5C%20%28e%2Cn%29%5C%20keep%5C%20%28d%2Cn%29)

![](https://latex.codecogs.com/gif.latex?6.%5C%20Encrypt%5C%20message%5C%20m%3A%5C%20c%5C%20%3D%5C%20m%5Ee%5C%20mod%5C%20n)

![](https://latex.codecogs.com/gif.latex?7.%5C%20Decrypt%5C%20ecrypted%5C%20message%5C%20c%3A%5C%20m%5C%20%3D%5C%20c%5Ed%5C%20mod%5C%20n)

### Generate strong primes
#### Generate primes
- Two important properties:
	- ***All primes (past 2 and 3) are of the forms 6n+1 and 6n-1*** ([proof](https://primes.utm.edu/notes/faq/six.html)).
	- If `a` is `n` bits number, `b` is `m` bits number. Than `a*b` will have at most `n + m + 2` bits number. (\[[2](#ref2)\]).
- With the two properties above, the below algorithm wil generate a prime

<p align="center">
  <img alt="drawing" width="480" height="270" src="./Images/genprime_alg.jpg" />
</p>

#### Generate strong primes
- The algorithm is followed the reference \[[3](#ref3)\].
- Generate a large random prime number `u`, then let `p` be the first prime in the sequence `i*u+1`, for *i=2,4,6,…*.

<p align="center">
  <img alt="drawing" width="480" height="270" src="./Images/genstrongprime_alg.jpg" />
</p>


### Find e and d

In step (3), (4). Do: 

- Pick `e` is a prime ![](https://latex.codecogs.com/gif.latex?%5Cgeq) 65535.
- Find d satifies ![](https://latex.codecogs.com/gif.latex?d%20%5Cgeq%20%5Csqrt%5B4%5D%7Bn%7D)

<p align="center">
  <img alt="drawing" width="550" height="400" src="./Images/genkey_alg.jpg" />
</p>

- *BinaryBezout algorithm* to find `d` satifies ![](https://latex.codecogs.com/gif.latex?ed%20&plus;%20x%5Cphi%20%3D%20gcd%28e%2C%5Cphi%29).

### Fast decryption using CRT
- From \[[4](#ref4)\]:

<p align="center">
  <img alt="drawing" src="https://latex.codecogs.com/gif.latex?%5Csmall%20p%2C%20q%20%5Cin%20%5Cmathcal%7BP%7D%2C%20p%20%5Cneq%20q%2C%20%5Cphi%20%3D%20%28p%20-1%29%28q-1%29%2C%20e%2Cd%20%5Cin%20%5Cmathbb%7BN%7D%2C%20gcd%28e%2C%5Cphi%29%3D1%2C%20ed%20%3D%201%5C%20mod%5C%20%5Cphi%2C%20n%20%3D%20pq" />
</p>

<p align="center">
  <img alt="drawing" src="https://latex.codecogs.com/gif.latex?%5Csmall%20%5CRightarrow%20x%20%3D%20c%5Ed%5C%20mod%20%5C%20n%5C%20also%5C%20a%5C%20unique%5C%20solution%5C%20of%5C%20the%5C%20system%5C%20of%5C%20equations%5E%7B%7D" />
</p>

<p align="center">
  <img alt="drawing" src="https://latex.codecogs.com/gif.latex?%5Csmall%20%5Cbegin%7Bcases%7D%20%26%20x%20%5Cequiv%20c%5E%7Bd_1%7D%5C%20%5Bmod%5C%20p%5D%20%5C%5C%20%26%20x%20%5Cequiv%20c%5E%7Bd_2%7D%5C%20%5Bmod%5C%20q%5D%20%5Cend%7Bcases%7D" />
</p>


## References
[1] Bùi Doãn Khanh và Nguyễn Đình Thúc. Giáo trình mã hóa thông tin: Lý thuyết và ứng dụng, 2004. <a name="ref1"></a>

[2] Alfred J. Menezes, Scott A. Vanstone, and Paul C. Van Oorschot. Handbook of Applied Cryptography. CRC Press, Inc., USA, 1st edition, 1996. <a name="ref2"></a>

[3] R. L. Rivest, A. Shamir, and L. Adleman. A method for obtaining digital signatures and public-key cryptosystems. Communications of the ACM, 21, 2 1978. <a name="ref3"></a>

[4] J.-J. Quisquater and C. Couvreur. Fast decipherment algorithm for rsa public-key cryptosystem. Electronics Letters, 18, 1982. <a name="ref4"></a>