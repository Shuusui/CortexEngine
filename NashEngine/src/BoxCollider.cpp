#include "..\include\BoxCollider.h"


void Nash::BoxCollider::IntersectDynamic()
{

}

void Nash::BoxCollider::IntersectStatic()
{
	for (int i = 0; i < m_nearStaticCollider.size(); i++)
	{
		if (CheckIntersection(m_nearStaticCollider[i]))
		{

		}
	}
}

bool Nash::BoxCollider::CheckIntersection(ICollider * coll)
{
	switch (coll->Type())
	{
	case Enums::EColliderType::BoxCollider:		
		break;
	case Enums::EColliderType::CapsuleCollider:
		break;
	case Enums::EColliderType::SphereCollider:
		break;
	}
	return false;
}

void Nash::BoxCollider::DeltaUpdate()
{

}

void Nash::BoxCollider::Update()
{
	
}

void Nash::BoxCollider::Start()
{
	ICollider::Start();
}
