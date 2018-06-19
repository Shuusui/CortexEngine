#include "include\CMaterial.h"
#define STB_IMAGE_IMPLEMENTATION

CE::Rendering::CMaterial::CMaterial()
	:m_pPixels(nullptr)
{
}

void CE::Rendering::CMaterial::ReadFile(const std::string & texturepath)
{
	m_pPixels = stbi_load(texturepath.c_str(), &m_texWidth, &m_texHeight, &m_texChannels, STBI_rgb_alpha);
}

void CE::Rendering::CMaterial::CreateTextureImage()
{
	VkDeviceSize imageSize = m_texWidth * m_texHeight * m_texChannels;

	m_mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(m_texWidth, m_texHeight)))) + 1;


	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	RENDERER->CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	void* data;
	RENDERER->MapData(data, m_pPixels, m_texImageMemory, imageSize);

	RENDERER->CreateImage(m_texWidth, m_texHeight, m_mipLevels, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_texImage, m_texImageMemory);

	RENDERER->TransitionImageLayout(m_texImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_mipLevels);
	RENDERER->CopyBufferToImage(stagingBuffer, m_texImage, static_cast<uint32_t>(m_texWidth), static_cast<uint32_t>(m_texHeight));

	vkDestroyBuffer(RENDERER->GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory, nullptr);

	RENDERER->GenerateMipmaps(m_texImage, m_texWidth, m_texHeight, m_mipLevels);
}


CE::Rendering::CMaterial::~CMaterial()
{
	stbi_image_free(m_pPixels);
}
