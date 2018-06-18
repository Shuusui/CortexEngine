#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace CE
{
	namespace Rendering
	{
		class CMaterial
		{
		private: 
			int m_texWidth;
			int m_texHeight; 
			int m_texChannels; 
			stbi_uc* m_pPixels;
		public: 
			CMaterial(); 
			//reads only jpeg files at the moment
			void ReadFile(const std::string& texturepath);

			~CMaterial();
		};
	}
}