#pragma once
#pragma region Internal Includes
#include "CMesh.h"
#include "CMaterial.h"
#include "ICComponent.h"
#include "Enums.h"
#include "ICObject.h"
#include "VulkanRenderer.h"
#pragma endregion 
#pragma region External Includes
#pragma endregion

namespace CE
{
	namespace Components
	{
		class CRenderComponent : public ICComponent
		{
		private:
			Rendering::CMesh* m_mesh;
			Rendering::CMaterial* m_material;
			VkDescriptorSet m_descriptorSet;
		public: 
			CRenderComponent(const uint_fast32_t& id); 
			void AddMesh(Rendering::CMesh* mesh);
			void AddMaterial(Rendering::CMaterial* mat);
			void Update() final; 
			void DeltaUpdate() final;
			VkDescriptorSet GetDescriptorSet() const { return m_descriptorSet; }
			void AllocateDescriptorSet();
			virtual ~CRenderComponent();
		};
	}
}