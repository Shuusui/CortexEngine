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
}

void CE::Components::CRenderComponent::AddMaterial(Rendering::CMaterial * mat)
{
	m_material = mat;
}

void CE::Components::CRenderComponent::Update()
{
	if (m_material && m_mesh)
	{

	}
}

void CE::Components::CRenderComponent::DeltaUpdate()
{
}


CE::Components::CRenderComponent::~CRenderComponent()
{
	delete m_material; 
	delete m_mesh;
}
