#pragma once
#pragma region Internal Includes
#include "CMesh.h"
#include "CMaterial.h"
#include "ICComponent.h"
#include "Enums.h"
#pragma endregion 
#pragma region External Includes
#pragma endregion

namespace CE
{
	namespace Components
	{
		class CRenderComponent : public Core::ICComponent
		{
		private:
			Core::CMesh* m_mesh;
			Core::CMaterial* m_material;

		public: 
			CRenderComponent(const uint_fast32_t& id); 
			void Update(); 
			virtual ~CRenderComponent();
		};
	}
}