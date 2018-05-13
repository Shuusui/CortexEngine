#pragma once


#pragma region Internal Includes
#pragma endregion 

#pragma region External Includes
#include <cstdint>
#include <string>
#pragma endregion 

namespace CortexEngine
{
	namespace Core
	{
		class ICComponent
		{
		private: 
			uint_fast32_t m_ID;
			std::string m_name;
			bool m_bUnique;
		public:
			ICComponent(const uint_fast32_t& id, const bool& unique = false) :m_ID(id), m_bUnique(unique) {};

			inline uint_fast32_t GetID() const { return m_ID; }

			inline bool IsUnique() const { return m_bUnique; }
		};
	}
}