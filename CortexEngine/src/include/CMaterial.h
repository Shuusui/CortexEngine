#pragma once
#pragma region Internal Includes
#include "InternalMacros.h"
#include "EngineManager.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <stb_image.h>
#include <vulkan/vulkan.h>
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
			VkImage Image; 
			VkDeviceMemory ImageMemory;
			VkImageView ImageView;
			VkSampler ImageSampler;
		};
		class CMaterial
		{
		private: 
			TexData m_diffTexData;
			TexData m_normalTexData;
			int m_mipLevels;
			CE::Components::CRenderComponent* m_renderComponent;
			std::vector<VkDescriptorImageInfo> m_imageInfos;
		public: 
			CMaterial(); 
			//reads only jpg files at the moment
			void AddDiffuse(const std::string& texturePath);
			void AddNormal(const std::string& texturePath);
			void ReadFile(const std::string& texturepath, TexData& data);
			void SetRenderComponent(CE::Components::CRenderComponent* renderComponent);
			void AddImageInfo(VkDescriptorImageInfo imageInfo);
			void Release();
			~CMaterial();
		private: 

			void CreateTextureImage(TexData& data);

			void CreateTextureImageView(TexData& data);

			void CreateTextureSampler(TexData& data);

			void CreateImageDescriptor();

			void CreateImageDescriptorInfo(TexData& data);
		};
	}
}