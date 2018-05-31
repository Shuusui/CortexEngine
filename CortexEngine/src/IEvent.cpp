#include "include\IEvent.h"
#include "include\EngineManager.h"

CE::Core::IEvent::IEvent()
{
	EngineManager::GetEventHandler()->AddEvent(this);
}
