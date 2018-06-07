#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#include "IEvent.h"
#pragma endregion 
#pragma region External Includes
#include <list>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class DirtyClassEvent : public IEvent
		{
		private: 
			ChangedVariable m_change;
		public: 
			DirtyClassEvent(const ChangedVariable& var) :m_change(var) {};
			ChangedVariable GetVar() const { return m_change; }

		};
	}
}