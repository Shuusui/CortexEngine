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
			std::vector<VkDescriptorImageInfo> m_imageInfos;
			VkDescriptorSet m_descriptorSet; 
			std::vector<VkWriteDescriptorSet> m_descriptorWrites;
		public: 
			CMaterial(); 
			//reads only jpg files at the moment
			void AddDiffuse(const std::string& texturePath);
			void AddNormal(const std::string& texturePath);
			void ReadFile(const std::string& texturepath, TexData& data);
			void AddImageInfo(VkDescriptorImageInfo imageInfo);
			void Release();
			std::vector<VkWriteDescriptorSet> GetDescriptorWrites() const; 
			~CMaterial();
		private: 

			void CreateTextureImage(TexData& data);

			void CreateTextureImageView(TexData& data);

			void CreateTextureSampler(TexData& data);

			void CreateDiffImageDescriptor();

			void CreateNormalImageDescriptor();

			void CreateImageDescriptorInfo(TexData& data);
		};
	}
}