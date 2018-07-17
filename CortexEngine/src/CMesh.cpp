#include "include\CMesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "include\CRenderComponent.h"


CE::Rendering::CMesh::CMesh()
{
	m_mesh = {};
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
	uint32_t count = 0;
	uint32_t i = 0;
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
				uniqueVertices[vertex] = static_cast<uint32_t>(m_mesh.Vertices.size());
				m_mesh.Vertices.push_back(vertex);
				if (count == 2)
				{
					glm::vec3& v0 = m_mesh.Vertices[i - 2].Pos; 
					glm::vec3& v1 = m_mesh.Vertices[i - 1].Pos; 
					glm::vec3& v2 = m_mesh.Vertices[i].Pos; 

					glm::vec2& uv0 = m_mesh.Vertices[i - 2].TexCoord; 
					glm::vec2& uv1 = m_mesh.Vertices[i - 1].TexCoord; 
					glm::vec2& uv2 = m_mesh.Vertices[i].TexCoord; 

					glm::vec3 deltaPos1 = v1 - v0; 
					glm::vec3 deltaPos2 = v2 - v0;

					glm::vec2 deltaUV1 = uv1 - uv0; 
					glm::vec2 deltaUV2 = uv2 - uv0;

					float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
					glm::vec3 tangent = (deltaPos1*deltaUV2.y - deltaPos2 * deltaUV1.y)*r; 
					glm::vec3 bitangent = ( deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

					m_mesh.Tangents.push_back(tangent);
					m_mesh.Tangents.push_back(tangent);
					m_mesh.Tangents.push_back(tangent);

					m_mesh.Bitangents.push_back(bitangent);
					m_mesh.Bitangents.push_back(bitangent);
					m_mesh.Bitangents.push_back(bitangent);
					count = 0;
				}

				count++;
				i++;
			}


			m_mesh.Indices.push_back(uniqueVertices[vertex]);
		}
	}
	if (m_mesh.Vertices.empty())
	{
		return;
	}
	//CreateVertexBuffer();
	//CreateIndexBuffer();
	//RENDERER->AddVertexBuffer(m_vertexBuffer);
	//RENDERER->SetIndexBuffer(m_indexBuffer);
	//RENDERER->SetIndices(m_indices);
}

void CE::Rendering::CMesh::Release()
{
	m_mesh.Release();

	delete this;
}

SMesh CE::Rendering::CMesh::GetMeshData()
{
	return m_mesh;
}

CE::Rendering::CMesh::~CMesh()
{
}

