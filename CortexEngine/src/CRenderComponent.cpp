#include "include\CRenderComponent.h"

CE::Components::CRenderComponent::CRenderComponent(const uint_fast32_t& id)
	:ICComponent(id, Enums::EComponentType::Render, true)
	,m_material(nullptr)
	,m_mesh(nullptr)
{
}

void CE::Components::CRenderComponent::Update()
{

}

CE::Components::CRenderComponent::~CRenderComponent()
{
	delete m_material; 
	delete m_mesh;
}
