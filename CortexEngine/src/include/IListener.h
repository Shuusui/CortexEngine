#pragma once
#pragma region Internal Includes
#include "IEvent.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class IListener
		{
		private:
			uint_fast16_t m_ID;
		public:
			void inline SetID(const uint_fast16_t& id) { m_ID = id; }

			virtual void ReceiveEvent(IEvent* event) = 0;
		};
	}
}