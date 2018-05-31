#pragma once
#pragma region Internal Includes
#include "IEvent.h"
#pragma endregion
#pragma region External Includes
#include <string>
#pragma endregion

namespace CE
{
	namespace Core
	{
		class MessageEvent : public IEvent
		{
		private: 
			std::string m_msg;
		public: 
			MessageEvent(const std::string& msg) : IEvent(), m_msg(msg) 
			{

			};
			std::string GetMsg() const 
			{
				return m_msg;
			};
		};
	}
}