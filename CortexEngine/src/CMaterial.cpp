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

void CE::Rendering::CMaterial::CreateTextureImage(int texWidth, int texHeight, void* pixels, VkImage& texImage, VkDeviceMemory& texImageMemory)
{
	VkDeviceSize imageSize = texWidth * texHeight * 4;

	m_mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;


	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(m_logicalDevice, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(m_logicalDevice, stagingBufferMemory);


	CreateImage(texWidth, texHeight, m_mipLevels, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, texImage, texImageMemory);

	TransitionImageLayout(texImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_mipLevels);
	CopyBufferToImage(stagingBuffer, texImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

	vkDestroyBuffer(m_logicalDevice, stagingBuffer, nullptr);
	vkFreeMemory(m_logicalDevice, stagingBufferMemory, nullptr);

	GenerateMipmaps(texImage, texWidth, texHeight, m_mipLevels);
}


CE::Rendering::CMaterial::~CMaterial()
{
	stbi_image_free(m_pPixels);
}
