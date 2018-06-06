#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#pragma endregion 
#pragma region External Includes
#pragma endregion 

namespace CE
{
	namespace Editor
	{
		class CEditorCamera
		{
		private: 
			Physics::Transform m_transform;
		public: 
			CEditorCamera(); 
			~CEditorCamera();
		private: 
		};
	}
}