#pragma once
#pragma region Internal Includes
#include "ICComponent.h"
#include "Rigidbody.h"
#include "NamespaceAlias.h"
#include "Enums.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#pragma endregion 

namespace CE
{
	namespace Components 
	{
		class CRigidbodyComponent : public ICComponent
		{
		public: 
			CRigidbodyComponent(const uint_fast32_t& id);
			void Update();
			virtual ~CRigidbodyComponent();
		};
	}
}