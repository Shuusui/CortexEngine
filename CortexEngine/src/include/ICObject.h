#pragma once
#pragma region Internal includes
#pragma endregion
#pragma region External includes
#include <cstdint>
#pragma endregion


namespace CortexEngine
{
	namespace Core
	{
		class ICObject
		{
		public:
			ICObject(); 

			virtual bool AddSubobject(ICObject* obj) = 0;

			virtual bool RemoveSubobject() = 0; 

			virtual ~ICObject(); 

		private: 
			uint_fast32_t m_ID; 
		};
	}
}