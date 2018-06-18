#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#include "VulkanRenderer.h"
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
			std::vector<Vertex> m_vertices; 
			std::vector<uint32_t> m_indices;
		public:
			CMesh(); 

			void LoadModel(const std::string& modelPath);

			~CMesh();

		};
	}
}