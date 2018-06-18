#include "include\CMaterial.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CE::Rendering::CMaterial::CMaterial()
	:m_pPixels(nullptr)
{
}

void CE::Rendering::CMaterial::ReadFile(const std::string & texturepath)
{
	m_pPixels = stbi_load(texturepath.c_str(), &m_texWidth, &m_texHeight, &m_texChannels, STBI_rgb_alpha);
}

CE::Rendering::CMaterial::~CMaterial()
{
	stbi_image_free(m_pPixels);
}
