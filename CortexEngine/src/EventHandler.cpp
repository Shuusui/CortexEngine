#include "include\EventHandler.h"

CECORE::EventHandler::EventHandler()
{
}

CECORE::EventHandler::~EventHandler()
{
	for (int i = m_listener.size(); i > 0; --i)
	{
		delete(m_listener[i]);
		m_listener.pop_back();
	}
	for (IEvent* e : m_eventQue)
	{
		delete(e);
		m_eventQue.pop_front();
	}
}

void CECORE::EventHandler::Update()
{
	if (!m_eventQue.empty())
	{
		SendEventToListener();
	}
}

void CECORE::EventHandler::AddEvent(IEvent* event)
{
	m_eventQue.push_back(event);
	SendEventToListener();
}

void CECORE::EventHandler::RegisterListener(IListener * listener)
{
	m_listener.push_back(listener);
	listener->SetID(m_listener.size());
}

void CECORE::EventHandler::RemoveListener(const uint_fast16_t & listenerID)
{
	m_listener[listenerID] = m_listener[m_listener.size()];
	delete(m_listener[m_listener.size()]);
	m_listener.pop_back();
}

void CECORE::EventHandler::SendEventToListener()
{
	if (m_listener.empty())
		return;
	for (IListener* listener : m_listener)
	{
		listener->ReceiveEvent(m_eventQue[0]);
	}
	m_eventQue.pop_front();
}
