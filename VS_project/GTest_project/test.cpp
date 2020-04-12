#include "gtest/gtest.h"
#include "../../Monomial.h"

TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Monomial, ta_default_constructor)
{
    ASSERT_NO_THROW(Monomial m);
}