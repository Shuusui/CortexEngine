#include "include\ICComponent.h"
#include "include\ICObject.h"


void CE::Components::ICComponent::AttachOnObject(CE::Core::ICObject * obj)
{
	m_obj = obj;
}
