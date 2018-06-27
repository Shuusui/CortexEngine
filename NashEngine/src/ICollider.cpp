#include "../include/ICollider.h"

//void Nash::ICollider::RemoveNearCollider(Nash::ICollider* coll)
//{
//	if (coll->IsStatic())
//	{
//		for (std::vector<ICollider*>::iterator it; it != m_nearStaticCollider.end(); ++it)
//		{
//			if (*it == coll)
//			{
//				m_nearStaticCollider.erase(it);
//			}
//		}
//	}
//	else
//	{
//		for (std::list<ICollider*>::iterator it; it != m_nearDynamicCollider.end(); ++it)
//		{
//			if (*it == coll)
//			{
//				m_nearDynamicCollider.erase(it);
//			}
//		}
//	}
//}