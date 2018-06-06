#include "include\CTransformComponent.h"

CE::Components::CTransformComponent::CTransformComponent(const Physics::Transform & transform, const uint_fast32_t& id)
	:ICComponent(id, Enums::EComponentType::Transform, true)
	, m_matrix()
{	
	//m_matrix.Translate(transform.Position);
	
	//m_matrix.Scale(transform.Scale);
}



CE::Components::CTransformComponent::~CTransformComponent()
{
}
