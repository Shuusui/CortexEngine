#include "include\CMesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "include\CRenderComponent.h"


CE::Rendering::CMesh::CMesh()
	:m_vertexBuffer(VK_NULL_HANDLE)
	,m_indexBuffer(VK_NULL_HANDLE)
{

}

void CE::Rendering::CMesh::LoadModel(const std::string& modelPath)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, modelPath.c_str())) {
		throw std::runtime_error(err);
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.Pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.TexCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};
			vertex.Normal = {
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};

			vertex.Color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(m_vertices.size());
				m_vertices.push_back(vertex);
			}


			m_indices.push_back(uniqueVertices[vertex]);
		}
	}
	if (m_vertices.empty())
	{
		return;
	}
	CreateVertexBuffer();
	CreateIndexBuffer();
	RENDERER->AddVertexBuffer(m_vertexBuffer);
	RENDERER->SetIndexBuffer(m_indexBuffer);
	RENDERER->SetIndices(m_indices);
}

void CE::Rendering::CMesh::Release()
{
	vkDeviceWaitIdle(RENDERER->GetLogicalDevice());

	m_vertices.clear();
	m_indices.clear();
	vkDestroyBuffer(RENDERER->GetLogicalDevice(), m_indexBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), m_indexBufferMemory, nullptr);

	vkDestroyBuffer(RENDERER->GetLogicalDevice(), m_vertexBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), m_vertexBufferMemory, nullptr);

	delete this;
}

void CE::Rendering::CMesh::SetRenderComponent(CE::Components::CRenderComponent* renderComponent)
{
	m_renderComponent = renderComponent;
}

void CE::Rendering::CMesh::CreateVertexBuffer()
{
	VkDeviceSize bufferSize = sizeof(m_vertices[0]) * m_vertices.size();
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	RENDERER->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, m_vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory);

	RENDERER->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_vertexBuffer, m_vertexBufferMemory);

	RENDERER->CopyBuffer(stagingBuffer, m_vertexBuffer, bufferSize);

	vkDestroyBuffer(RENDERER->GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory, nullptr);
}

void CE::Rendering::CMesh::CreateIndexBuffer()
{
	VkDeviceSize bufferSize = sizeof(m_indices[0]) * m_indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	RENDERER->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, m_indices.data(), (size_t)bufferSize);
	vkUnmapMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory);

	RENDERER->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		m_indexBuffer, m_indexBufferMemory);

	RENDERER->CopyBuffer(stagingBuffer, m_indexBuffer, bufferSize);

	vkDestroyBuffer(RENDERER->GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), stagingBufferMemory, nullptr);
}

CE::Rendering::CMesh::~CMesh()
{
}
