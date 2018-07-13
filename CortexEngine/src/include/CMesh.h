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
	namespace Rendering
	{
		class CMesh
		{
		private: 
			SMesh m_mesh;
			/*std::vector<Vertex> m_vertices;
			std::vector<uint32_t> m_indices;
			std::vector<glm::vec3> m_tangents;
			std::vector<glm::vec3> m_bitangents;
			VkBuffer m_vertexBuffer;
			VkDeviceMemory m_vertexBufferMemory;
			VkBuffer m_indexBuffer;
			VkDeviceMemory m_indexBufferMemory;
			CE::Components::CRenderComponent* m_renderComponent;*/
			uint32_t m_VkID;
		public:
			CMesh(); 

			void LoadModel(const std::string& modelPath);

			void Release();

			~CMesh();
		private: 

			void CreateVertexBuffer(std::vector<Vertex> vertices, VkBuffer vertexBuffer, VkDeviceMemory vertexBufferMemory);

			void CreateIndexBuffer();

		};
	}
}