#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#pragma endregion 
#pragma region External Includes
#pragma endregion

namespace CE
{
	namespace Rendering
	{
		class CMesh
		{
		private: 
			MeshData m_data;
		public:
			CMesh(const std::string& name, const MeshData& data); 
			~CMesh();

		};
	}
}