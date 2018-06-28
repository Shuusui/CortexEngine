#include "gtest\gtest.h"
#include "Vector3.h"

TEST(FVector3, defaultCtor)
{
	Nash::FVector3 vec = Nash::FVector3();
	Nash::FVector3 vec1 = Nash::FVector3(0,0,0);
	EXPECT_FLOAT_EQ(0.0f, vec.X);
	EXPECT_FLOAT_EQ(0.0f, vec.Y); 
	EXPECT_FLOAT_EQ(0.0f, vec.Z);
	EXPECT_EQ(true, vec == vec1);
}

TEST(FVector3, paramCtor)
{
	Nash::FVector3 vec = Nash::FVector3(9.4123123f, 12.421315f, 89.2325f);
	EXPECT_FLOAT_EQ(9.4123123f, vec.X);
	EXPECT_FLOAT_EQ(12.421315f, vec.Y);
	EXPECT_FLOAT_EQ(89.2325f, vec.Z);
	EXPECT_EQ(Nash::FVector3(9.4123123f, 12.421315f, 89.2325f), vec);
}