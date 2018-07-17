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
			uint32_t m_VkID;
		public:
			CMesh(); 

			void LoadModel(const std::string& modelPath);

			void Release();

			SMesh GetMeshData();

			~CMesh();
		private: 

		};
	}
}