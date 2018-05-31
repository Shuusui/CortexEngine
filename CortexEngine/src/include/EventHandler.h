#pragma once
#pragma region Internal Includes
#include "NamespaceAlias.h"
#include "IListener.h"
#include "IEvent.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <deque>
#include <vector>
#include <cstdint>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class EventHandler
		{
		private:
			std::deque<IEvent*> m_eventQue;
			std::vector<IListener*> m_listener;
		public:
			EventHandler();
			~EventHandler();
			void Update();
			void AddEvent(IEvent* event);
			void RegisterListener(IListener* listener);
			void RemoveListener(const uint_fast16_t& listenerID);
		private:
			void SendEventToListener();
		};
	}
}