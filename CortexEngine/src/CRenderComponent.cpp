#include "include\CRenderComponent.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

uint32_t g_modelRotation = 0;


CE::Components::CRenderComponent::CRenderComponent(const uint_fast32_t& id)
	:ICComponent(id, Enums::EComponentType::Render, true)
	,m_material(nullptr)
	,m_mesh(nullptr)
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
	m_material->SetRenderComponent(this);
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
	AllocateDescriptorSet();
	CreateUniformBuffer();
}

void CE::Components::CRenderComponent::AllocateDescriptorSet()
{
	VkDescriptorSetLayout layouts[] = { RENDERER->GetDescriptorLayout() };
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = RENDERER->GetDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = layouts;

	if (vkAllocateDescriptorSets(RENDERER->GetLogicalDevice(), &allocInfo, &m_descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor set!");
	}
	RENDERER->AddDescriptorSet(m_descriptorSet);
}

void CE::Components::CRenderComponent::CreateUniformBuffer()
{
	VkDeviceSize bufferSize = sizeof(CE::Rendering::UniformBufferObject);
	RENDERER->CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		m_uniformBuffer, m_uniformBufferMemory);
	CreateUniformBufferInfo();
	CreateUniformBufferWrite();
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
	delete this;
}

CE::Components::CRenderComponent::~CRenderComponent()
{
}

void CE::Components::CRenderComponent::CreateUniformBufferInfo()
{
	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = m_uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(CE::Rendering::UniformBufferObject);
	AddBufferInfo(bufferInfo);
}

void CE::Components::CRenderComponent::UpdateUniformBuffer()
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	CE::Rendering::UniformBufferObject ubo = {};
	ubo.Model = glm::rotate(glm::mat4(1.0f), time* glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.View = glm::lookAt(glm::vec3(40.0f, 40.0f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.Proj = glm::perspective(glm::radians(45.0f), RENDERER->GetExtent().width/ (float)RENDERER->GetExtent().height, 0.1f, 100.0f);

	ubo.Proj[1][1] *= -1;

	void* data;
	vkMapMemory(RENDERER->GetLogicalDevice(), m_uniformBufferMemory, 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(RENDERER->GetLogicalDevice(), m_uniformBufferMemory);

}