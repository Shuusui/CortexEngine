#include ".//include/Console.h"

CE::Core::Console::Console()
{
}

CE::Core::Console::~Console()
{
}

bool CE::Core::Console::ReceiveEvent(IEvent* event)
{
	if (!dynamic_cast<MessageEvent*>(event)) //TODO: Change the way to check if it's a messageevent
		return false;
	printf(((MessageEvent*)event)->GetMsg().c_str());
	return true;
}