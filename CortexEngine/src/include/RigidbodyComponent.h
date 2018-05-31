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
	namespace Physics
	{
		class RigidbodyComponent : public CECORE::ICComponent
		{
		public: 
			RigidbodyComponent(const uint_fast32_t& id);

			~RigidbodyComponent();
		};
	}
}