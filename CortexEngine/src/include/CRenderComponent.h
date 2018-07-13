#pragma once
#pragma region Internal Includes
#include "CMesh.h"
#include "CMaterial.h"
#include "ICComponent.h"
#include "Enums.h"
#include "VulkanRenderer.h"
#include "CortexStructs.h"
#include "InternalMacros.h"
#pragma endregion 
#pragma region External Includes
#include <glm/gtc/matrix_transform.hpp>
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
			VkBuffer m_uniformBuffer;
			VkDeviceMemory m_uniformBufferMemory;	
			std::vector<VkDescriptorBufferInfo> m_bufferInfos;
			std::vector<VkWriteDescriptorSet> m_descriptorWrites;
			glm::mat4 m_modelMat;
		public: 
			CRenderComponent(const uint_fast32_t& id); 
			void AddMesh(Rendering::CMesh* mesh);
			void AddMaterial(Rendering::CMaterial* mat);
			void Update() final; 
			void DeltaUpdate() final;
			void Init();
			void CreateUniformBuffer();
			void CreateUniformBufferWrite();
			void AddBufferInfo(VkDescriptorBufferInfo bufferInfo);
			virtual void Release() final;
			virtual ~CRenderComponent();
		private: 
			void CreateUniformBufferInfo();
			void UpdateUniformBuffer();
			void SetModelMatrix();

		};
	}
}