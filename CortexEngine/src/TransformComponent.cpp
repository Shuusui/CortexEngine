#include "include\TransformComponent.h"

CE::Physics::TransformComponent::TransformComponent(const Transform & transform, const uint_fast32_t& id)
	:CECORE::ICComponent(id, CECORE::Enums::EComponentType::Transform)
	, m_matrix()
{	
	m_matrix.Translate(transform.Position);
	
	m_matrix.Scale(transform.Scale);
}



CE::Physics::TransformComponent::~TransformComponent()
{
}
