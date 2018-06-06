#pragma once
#pragma region Internal Includes
#include "ICColllider.h"
#include "ICComponent.h"
#include "Enums.h"
#pragma endregion
#pragma region External Includes
#pragma endregion 

namespace CE
{
	namespace Components
	{
		class CColliderComponent : public ICComponent
		{
		private: 
			Internal::ICCollider* m_collider;
		public: 
			CColliderComponent(const uint_fast32_t& id, Internal::ICCollider* coll);
			void Update();
			bool SwitchColliderType(Internal::ICCollider* coll);
			~CColliderComponent();
		};
	}
}