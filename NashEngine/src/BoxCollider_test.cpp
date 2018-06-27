#include "gtest\gtest.h"
#include "BoxCollider.h"

Nash::BoxCollider* pColl = nullptr;

TEST(BoxCollider, isTrigger)
{
	pColl = new Nash::BoxCollider(Nash::FVector3(1, 1, 1), Nash::FVector3(0, 0, 0));
	EXPECT_EQ(false, pColl->IsTrigger());
	pColl->SetIsTrigger(true);
	EXPECT_EQ(true, pColl->IsTrigger());
}

TEST(BoxCollider, isStatic)
{
	EXPECT_EQ(false, pColl->IsStatic());
	pColl->SetIsStatic(true);
	EXPECT_EQ(true, pColl->IsStatic());
}

TEST(BoxCollider, positions)
{
	EXPECT_EQ(Nash::FVector3(1,1,1), pColl->GlobalPosition());
	EXPECT_EQ(Nash::FVector3(0, 0, 0), pColl->LocalPosition());
}

TEST(BoxCollider, size)
{
	EXPECT_EQ(Nash::FVector3(1, 1, 1), pColl->GetSize());
}
TEST(BoxCollider, extents)
{
	EXPECT_EQ(Nash::FVector3(.5f, .5f, .5f), pColl->GetExtents());
}