#include "include\CMesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


CE::Rendering::CMesh::CMesh()
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

			vertex.Color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(m_vertices.size());
				m_vertices.push_back(vertex);
			}


			m_indices.push_back(uniqueVertices[vertex]);
		}
	}
}

CE::Rendering::CMesh::~CMesh()
{

}
