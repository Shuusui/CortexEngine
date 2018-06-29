#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#include "VulkanRenderer.h"
#include "InternalMacros.h"
#pragma endregion 
#pragma region External Includes
#include <unordered_map>
#include <vector>
#pragma endregion

namespace CE
{
	namespace Components {
		class CRenderComponent; 
	}
	namespace Rendering
	{
		class CMesh
		{
		private: 
			std::vector<Vertex> m_vertices; 
			std::vector<uint32_t> m_indices;
			std::vector<glm::vec3> m_tangents;
			std::vector<glm::vec3> m_bitangents;
			VkBuffer m_vertexBuffer; 
			VkDeviceMemory m_vertexBufferMemory; 
			VkBuffer m_indexBuffer; 
			VkDeviceMemory m_indexBufferMemory;
			CE::Components::CRenderComponent* m_renderComponent;
		public:
			CMesh(); 

			void LoadModel(const std::string& modelPath);

			void Release();

			void SetRenderComponent(CE::Components::CRenderComponent* renderComponent);

			~CMesh();
		private: 
			void ComputeTangents();

			void CreateVertexBuffer();

			void CreateIndexBuffer();

		};
	}
}