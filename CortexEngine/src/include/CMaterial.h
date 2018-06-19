#pragma once
#pragma region Internal Includes
#include "EngineManager.h"
#include "InternalMacros.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <stb_image.h>
#include <vulkan\vulkan.h>
#include <algorithm>
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
			VkImage m_texImage; 
			VkDeviceMemory m_texImageMemory;
			int m_mipLevels;
		public: 
			CMaterial(); 
			//reads only jpeg files at the moment
			void ReadFile(const std::string& texturepath);

			void CreateTextureImage();


			~CMaterial();
		};
	}
}