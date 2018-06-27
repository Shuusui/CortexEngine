#include "include\ICObject.h"

void CE::Core::ICObject::Update()
{
	for (Components::ICComponent* comp : m_components)
	{
		comp->Update();
		comp->DeltaUpdate();
	}
}

void CE::Core::ICObject::Release()
{
	for (Components::ICComponent* comp : m_components)
	{
		comp->Release();
	}
	delete this;
}

CE::Core::ICObject::~ICObject()
{
	for (const auto& subObject : m_subObjects)
	{
		delete(subObject);
	}
}
