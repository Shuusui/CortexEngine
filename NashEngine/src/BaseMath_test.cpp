#include "gtest\gtest.h"
#include "BaseMath.h"

TEST(baseMath, AbsF)
{
	float x = -1.5f;
	x = Nash::AbsF(x);
	EXPECT_FLOAT_EQ(x, 1.5f);
	x = Nash::AbsF(x);
	EXPECT_FLOAT_EQ(x, 1.5f);
}

TEST(baseMath, AbsD)
{
	double x = -2.5f; 
	x = Nash::AbsD(x);
	EXPECT_FLOAT_EQ(x, 2.5f);
	x = Nash::AbsD(x);
	EXPECT_FLOAT_EQ(x, 2.5f);
}

TEST(baseMath, CompareF)
{

	EXPECT_TRUE(Nash::Compare(1.511232553123123f, 1.511232553112351f));
	EXPECT_FALSE(Nash::Compare(1.5112324f, 1.5112325f));
	//TODO: Add test for CompareD
}
TEST(baseMath, SqrtF)
{
	float x = 9; 
	EXPECT_FLOAT_EQ(3.0f, Nash::Sqrt(x));
}

TEST(baseMath, SquareF)
{
	float x = 2; 
	EXPECT_FLOAT_EQ(4.0f, Nash::Square(x));
}

TEST(baseMath, SquareD)
{
	double x = 2; 
	EXPECT_FLOAT_EQ(4.0f, Nash::Square(x));
}
