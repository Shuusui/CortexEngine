#include "include\CMaterial.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "include\CRenderComponent.h"

CE::Rendering::CMaterial::CMaterial()
	:m_diffImage(VK_NULL_HANDLE)
	,m_diffImageMemory(VK_NULL_HANDLE)
	,m_texImageView(VK_NULL_HANDLE)
	,m_texSampler(VK_NULL_HANDLE)
	,m_mipLevels(0)
{
}

void CE::Rendering::CMaterial::AddDiffuse(const std::string & texturePath)
{
	m_diffTexData = ReadFile(texturePath);
}

void CE::Rendering::CMaterial::AddNormal(const std::string & texturePath)
{
	m_normalTexData = ReadFile(texturePath);
}

CE::Rendering::TexData CE::Rendering::CMaterial::ReadFile(const std::string & texturepath)
{
	struct TexData data = {};
	data.Pixels = stbi_load(texturepath.c_str(), &data.TexWidth, &data.TexHeight, &data.TexChannels, STBI_rgb_alpha);
	if (!data.Pixels)
		return data; //TODO return a valid null value
	return data;
}

void CE::Rendering::CMaterial::SetRenderComponent(CE::Components::CRenderComponent* renderComponent)
{
	m_renderComponent = renderComponent;
	CreateTextureImage();
	CreateTextureImageView();
	CreateTextureSampler();
}

void CE::Rendering::CMaterial::AddImageInfo(VkDescriptorImageInfo imageInfo)
{
	m_imageInfos.push_back(imageInfo);
}

void CE::Rendering::CMaterial::Release()
{
	vkDeviceWaitIdle(RENDERER->GetLogicalDevice());

	stbi_image_free(m_diffTexData.Pixels);

	vkDestroyImageView(RENDERER->GetLogicalDevice(), m_texImageView, nullptr);

	vkDestroyImage(RENDERER->GetLogicalDevice(), m_diffImage, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), m_diffImageMemory, nullptr);

	vkDestroySampler(RENDERER->GetLogicalDevice(), m_texSampler, nullptr);

	delete this;
}

void CE::Rendering::CMaterial::CreateTextureImage()
{
	VkDeviceSize imageSize = m_diffTexData.TexWidth * m_diffTexData.TexHeight * 4;

	m_mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(m_diffTexData.TexWidth, m_diffTexData.TexHeight)))) + 1;


	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	RENDERER->CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	void* data = nullptr;
	RENDERER->MapData(data, m_diffTexData.Pixels, stagingBufferMemory, imageSize);

	RENDERER->CreateImage(m_diffTexData.TexWidth, m_diffTexData.TexHeight, m_mipLevels, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_diffImage, m_diffImageMemory);
	
	RENDERER->TransitionImageLayout(m_diffImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_mipLevels);
	RENDERER->CopyBufferToImage(stagingBuffer, m_diffImage, static_cast<uint32_t>(m_diffTexData.TexWidth), static_cast<uint32_t>(m_diffTexData.TexHeight));

	vkDestroyBuffer(RENDERER->GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory, nullptr);

	RENDERER->GenerateMipmaps(m_diffImage, m_diffTexData.TexWidth, m_diffTexData.TexHeight, m_mipLevels);
}

void CE::Rendering::CMaterial::CreateTextureImageView()
{
	m_texImageView = RENDERER->CreateImageView(m_diffImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, m_mipLevels);
}

void CE::Rendering::CMaterial::CreateTextureSampler()
{
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = static_cast<float>(m_mipLevels);

	if (vkCreateSampler(RENDERER->GetLogicalDevice(), &samplerInfo, nullptr, &m_texSampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
	CreateImageDescriptor();
}

void CE::Rendering::CMaterial::BindSampler()
{
	VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
}

void CE::Rendering::CMaterial::CreateImageDescriptor()
{
	CreateImageDescriptorInfo();

	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = m_renderComponent->GetDescriptorSet();
	descriptorWrite.dstBinding = 1;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pImageInfo = m_imageInfos.data();

	RENDERER->UpdateDescriptorSets(descriptorWrite);
}

void CE::Rendering::CMaterial::CreateImageDescriptorInfo()
{
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = m_texImageView;
	imageInfo.sampler = m_texSampler;
	AddImageInfo(imageInfo);
}


CE::Rendering::CMaterial::~CMaterial()
{
}
