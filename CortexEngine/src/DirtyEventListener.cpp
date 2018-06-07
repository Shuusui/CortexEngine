#include "include\DirtyEventListener.h"

CE::Core::DirtyEventListener::DirtyEventListener()
{
}

CE::Core::DirtyEventListener::~DirtyEventListener()
{
}

bool CE::Core::DirtyEventListener::ReceiveEvent(IEvent * event)
{
	DirtyClassEvent* dEvent = dynamic_cast<DirtyClassEvent*>(event);
	if(!dEvent)
	{
		return false;
	}
	ChangedVariable var = dEvent->GetVar();
	std::fstream file; 
	file.open(var.FilePath, std::ios::out);
	if (!file.is_open())
	{
		//TODO: add message
		return false;
	}
	file.seekg(0, var.Line);
	file.write(var.Change.c_str(),var.Change.size());
	delete dEvent;
	return true;
}
