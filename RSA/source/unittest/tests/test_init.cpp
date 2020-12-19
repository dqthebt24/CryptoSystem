#include "pch.h"
#include "bigint.h"

TEST(TestInitialize, InitWithNumberBits) {
	BigInt a(4);
	EXPECT_EQ(4, a.getLen());
}