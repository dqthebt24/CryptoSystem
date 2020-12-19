#include "pch.h"
#include "bigint.h"
#include <string>

TEST(TestInitialize, InitWithNumberBits) {
	BigInt a(4);
	EXPECT_EQ(4, a.getLen());
	EXPECT_EQ('1', a.getDigits()[0]);
}

TEST(TestInitialize, InitWithNumberZero)
{
	BigInt a(0);
	EXPECT_EQ(0, a.getLen());
	EXPECT_EQ(nullptr, a.getDigits());
}

TEST(TestInitialize, InitWithChars)
{
	string str1("100001"), str2("001001");
	BigInt a(str1.c_str());
	EXPECT_EQ(6, a.getLen());
	EXPECT_EQ(str1, string(a.getDigits()));

	BigInt b(str2.c_str());
	EXPECT_EQ(6, b.getLen());
	EXPECT_EQ(str2, string(b.getDigits()));
}
