#pragma once
#pragma region Internal Includes
#include "IListener.h"
#include "NamespaceAlias.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class MessageListener : public IListener
		{
		private:
			std::string m_msg;
		public:

		};
	}
}