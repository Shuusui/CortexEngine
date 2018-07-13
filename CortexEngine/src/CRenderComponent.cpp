#include "include\CRenderComponent.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

uint32_t g_modelRotation = 0;


CE::Components::CRenderComponent::CRenderComponent(const uint_fast32_t& id)
	:ICComponent(id, Enums::EComponentType::Render, true)
	,m_material(nullptr)
	,m_mesh(nullptr)
	, m_modelMat(1)
{
}

void CE::Components::CRenderComponent::AddMesh(Rendering::CMesh * mesh)
{
	m_mesh = mesh;
	m_mesh->SetRenderComponent(this);
}

void CE::Components::CRenderComponent::AddMaterial(Rendering::CMaterial * mat)
{
	m_material = mat;
	for (VkWriteDescriptorSet descWrite : mat->GetDescriptorWrites())
	{
		RENDERER->UpdateDescriptorSets(descWrite);
	}
}

void CE::Components::CRenderComponent::Update()
{
	UpdateUniformBuffer();
}

void CE::Components::CRenderComponent::DeltaUpdate()
{
}


void CE::Components::CRenderComponent::Init()
{
	RENDERER->AllocateDescriptorSet(m_descriptorSet);
	CreateUniformBuffer();
}

void CE::Components::CRenderComponent::CreateUniformBuffer()
{
	VkDeviceSize bufferSize = sizeof(CE::Rendering::UniformBufferObject);
	RENDERER->CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_uniformBuffer, m_uniformBufferMemory);
	CreateUniformBufferInfo();
	CreateUniformBufferWrite();
}


void CE::Components::CRenderComponent::CreateUniformBufferInfo()
{
	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = m_uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(CE::Rendering::UniformBufferObject);
	AddBufferInfo(bufferInfo);
}
void CE::Components::CRenderComponent::CreateUniformBufferWrite()
{
	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = m_descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = m_bufferInfos.data();
	m_descriptorWrites.push_back(descriptorWrite);
	RENDERER->UpdateDescriptorSets(descriptorWrite);
}


void CE::Components::CRenderComponent::AddBufferInfo(VkDescriptorBufferInfo bufferInfo)
{
	m_bufferInfos.push_back(bufferInfo);
}


void CE::Components::CRenderComponent::Release()
{
	m_mesh->Release();
	m_material->Release();
	vkDestroyBuffer(RENDERER->GetLogicalDevice(),m_uniformBuffer, nullptr);
	vkFreeMemory(RENDERER->GetLogicalDevice(), m_uniformBufferMemory, nullptr);
	delete this;
}

CE::Components::CRenderComponent::~CRenderComponent()
{
}

void CE::Components::CRenderComponent::UpdateUniformBuffer()
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	CE::Rendering::UniformBufferObject ubo = {};
	glm::mat4 initRot = glm::mat4(1);
	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_obj->GetTransform().Position[0], m_obj->GetTransform().Position[1], m_obj->GetTransform().Position[2]));
	ubo.Model =  transMat*initRot;
	RENDERER->GetCamera()->ComputeMatrix(ubo);

	ubo.Proj[1][1] *= -1;

	ubo.MV3x3 = glm::mat3x3(ubo.View * ubo.Model);

	void* data;
	vkMapMemory(RENDERER->GetLogicalDevice(), m_uniformBufferMemory, 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(RENDERER->GetLogicalDevice(), m_uniformBufferMemory);

}

void CE::Components::CRenderComponent::SetModelMatrix()
{

}
