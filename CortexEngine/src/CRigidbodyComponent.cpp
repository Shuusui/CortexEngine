#include "include\CRigidbodyComponent.h"

CE::Components::CRigidbodyComponent::CRigidbodyComponent(const uint_fast32_t & id)
	:CECORE::ICComponent(id, Enums::EComponentType::Rigidbody, true)
{

}

void CE::Components::CRigidbodyComponent::Update()
{
}

CE::Components::CRigidbodyComponent::~CRigidbodyComponent()
{
}
