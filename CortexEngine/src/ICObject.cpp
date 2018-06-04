#include "include\ICObject.h"

void CE::Core::ICObject::Update()
{
	for (ICComponent* comp : m_components)
	{
		comp->Update();
		comp->DeltaUpdate();
	}
}
