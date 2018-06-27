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
	namespace Components {
		class CRenderComponent;
	}
	namespace Rendering
	{
		struct TexData
		{
			int TexWidth; 
			int TexHeight; 
			int TexChannels;
			stbi_uc* Pixels;
		};
		class CMaterial
		{
		private: 
			/*int m_texWidth;
			int m_texHeight;
			stbi_uc* m_pPixels;*/
			TexData m_diffTexData;
			VkImage m_diffImage; 
			VkDeviceMemory m_diffImageMemory;
			VkImage m_normalImage; 
			VkDeviceMemory m_normalImageMemory;
			int m_mipLevels;
			VkImageView m_texImageView;
			VkSampler m_texSampler;
			CE::Components::CRenderComponent* m_renderComponent;
			std::vector<VkDescriptorImageInfo> m_imageInfos;
		public: 
			CMaterial(); 
			//reads only jpg files at the moment
			void AddNewTexture(const std::string& texturePath);
			TexData ReadFile(const std::string& texturepath);
			void SetRenderComponent(CE::Components::CRenderComponent* renderComponent);
			void AddImageInfo(VkDescriptorImageInfo imageInfo);
			void Release();
			~CMaterial();
		private: 

			void CreateTextureImage();

			void CreateTextureImageView();

			void CreateTextureSampler();

			void BindSampler(); 

			void CreateImageDescriptor();

			void CreateImageDescriptorInfo();
		};
	}
}