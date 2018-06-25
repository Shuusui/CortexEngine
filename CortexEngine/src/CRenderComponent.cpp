#include "include\CRenderComponent.h"


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
	CreateUniformBufferWrite();
}

void CE::Components::CRenderComponent::CreateUniformBufferWrite()
{
	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = m_uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(CE::Rendering::UniformBufferObject);

	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = m_descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &bufferInfo;

	BindUniformBuffer();
	RENDERER->UpdateDescriptorSets(descriptorWrite);
}

void CE::Components::CRenderComponent::BindUniformBuffer()
{
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	//RENDERER->AddDescriptorLayoutBinding(uboLayoutBinding);
}

CE::Components::CRenderComponent::~CRenderComponent()
{
	delete m_material; 
	delete m_mesh;
}
