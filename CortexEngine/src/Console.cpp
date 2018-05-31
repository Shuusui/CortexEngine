#include ".//include/Console.h"

CE::Core::Console::Console()
{
}

CE::Core::Console::~Console()
{
}

void CE::Core::Console::ReceiveEvent(IEvent* event)
{
	if (!(MessageEvent*)event)
		return;
	printf(((MessageEvent*)event)->GetMsg().c_str());
	delete event;
}
