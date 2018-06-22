#pragma once
#pragma region Internal Includes
#include "InternalMacros.h"
#include "EngineManager.h"
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
			VkImageView m_texImageView;
			VkSampler m_texSampler;
		public: 
			CMaterial(); 
			//reads only jpeg files at the moment
			void ReadFile(const std::string& texturepath);
			~CMaterial();
		private: 

			void CreateTextureImage();

			void CreateTextureImageView();

			void CreateTextureSampler();


		};
	}
}