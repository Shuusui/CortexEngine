#pragma once
#pragma region Internal Includes
#include "NamespaceAlias.h"
#include "MessageListener.h"
#include "IEvent.h"
#include "MessageEvent.h"
#pragma endregion 
#pragma region External Includes
#include <iostream>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class Console : public MessageListener
		{

		public:
			Console();
			~Console();
			virtual bool ReceiveEvent(IEvent* event) final;
		};
	}
}