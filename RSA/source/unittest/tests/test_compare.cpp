#include "pch.h"
#include "bigint.h"
#include <string>

TEST(TestCompare, CompareEqual)
{
	BigInt a("100000000011101"), b("100000000011101");
	EXPECT_EQ(true, a == b);

	BigInt c("000000000011101"), d("100000000011100");
	EXPECT_EQ(false, c == d);
}

TEST(TestCompare, CompareGreater)
{
	BigInt a("100000000011101"), b("100000000011100");
	EXPECT_EQ(false, a == b);
	EXPECT_EQ(true, a >= b);
	EXPECT_EQ(true, a > b);

	BigInt c("000000000011101"), d("100000000011100");
	EXPECT_EQ(false, c == d);
	EXPECT_EQ(false, c >= d);
	EXPECT_EQ(false, c > d);

	// TDDB[unittest]
	//BigInt e("000000000011101"), f("1000001");
	//EXPECT_EQ(false, e >= f);
	//EXPECT_EQ(false, e >= f); // Need to check here again!
	//EXPECT_EQ(false, e > f); // Need to check here again!


}