#pragma once
#pragma region Internal Includes
#include "IListener.h"
#include "DirtyClassEvent.h"
#pragma endregion 
#pragma region External Includes
#include <fstream>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class DirtyEventListener :public IListener
		{
		public:
			DirtyEventListener();
			~DirtyEventListener();

			virtual bool ReceiveEvent(IEvent* event) final;
		};
	}
}