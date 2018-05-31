#include "include\RigidbodyComponent.h"

CE::Physics::RigidbodyComponent::RigidbodyComponent(const uint_fast32_t & id)
	:CECORE::ICComponent(id, CECORE::Enums::EComponentType::Rigidbody)
{

}

CE::Physics::RigidbodyComponent::~RigidbodyComponent()
{
}
