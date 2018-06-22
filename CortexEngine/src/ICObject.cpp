#include "include\ICObject.h"

void CE::Core::ICObject::Update()
{
	for (Components::ICComponent* comp : m_components)
	{
		comp->Update();
		comp->DeltaUpdate();
	}
}

CE::Core::ICObject::~ICObject()
{
	for (const auto& component: m_components)
	{
		delete (component);
	}
	for (const auto& subObject : m_subObjects)
	{
		delete(subObject);
	}
}
