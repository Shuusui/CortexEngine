#pragma once
#pragma region Internal includes
#include "CEditorCamera.h"
#pragma endregion
#pragma region External includes
#include <cstdint>
#pragma endregion


namespace CE
{
	namespace Editor
	{
		class CEditor
		{
		private: 
			CEditorCamera* m_pEdiCam; 
		public: 
			CEditor(); 
			~CEditor();
		private: 

		};
	}
}