#include <gtest/gtest.h>
#include <string>
#include "../bigint.h"
TEST(TestInitialize, InitWithLen) {
	BigInt a(4);
	ASSERT_EQ(4, a.getLen());
	ASSERT_EQ('1', a.getDigits()[0]);
}

TEST(TestInitialize, InitWithChars) {
	BigInt a("1001");
	ASSERT_EQ(4, a.getLen());
	ASSERT_EQ("1001", string(a.getDigits()));
}
