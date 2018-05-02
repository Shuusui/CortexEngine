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
			ICObject() = delete;

			ICObject(const uint_fast32_t& id) : m_ID(id){};

			ICObject(const ICObject& obj) { m_ID = obj.m_ID; }

			virtual bool AddSubobject(ICObject* obj) = 0;

			virtual bool RemoveSubobject() = 0; 

			virtual uint_fast32_t GetID() const final { return m_ID;  }
			
			virtual ~ICObject() = 0; 

		private: 
			uint_fast32_t m_ID; 
		};
	}
}