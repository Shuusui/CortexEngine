#include "include\ICObject.h"

void CE::Core::ICObject::Update()
{
	for (Components::ICComponent* comp : m_components)
	{
		comp->Update();
		comp->DeltaUpdate();
	}
}
