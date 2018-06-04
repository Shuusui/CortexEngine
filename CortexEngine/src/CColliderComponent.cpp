#include "include\CColliderComponent.h"

CE::Components::CColliderComponent::CColliderComponent(const uint_fast32_t& id, Internal::ICCollider * coll)
	:ICComponent(id, Enums::EComponentType::Collider, false)
	,m_collider(coll)
{
}

void CE::Components::CColliderComponent::Update()
{
}

bool CE::Components::CColliderComponent::SwitchColliderType(Internal::ICCollider * coll)
{
	m_collider = coll;
	if (m_collider)
		return true;
	return false;
}

CE::Components::CColliderComponent::~CColliderComponent()
{
	delete m_collider;
}
