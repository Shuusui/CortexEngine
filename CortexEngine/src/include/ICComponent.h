#pragma once
#pragma region Internal Includes
#include "Enums.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#include <string>
#pragma endregion 

namespace CE
{
	namespace Components
	{
		class ICComponent
		{
		private: 
			uint_fast32_t m_ID;
			std::string m_name;
			bool m_bUnique;
			Enums::EComponentType m_componentType;
		public:
			ICComponent(const uint_fast32_t& id, const Enums::EComponentType& compType, const bool& unique = false) :m_ID(id), m_bUnique(unique), m_componentType(compType) {};

			inline uint_fast32_t GetID() const { return m_ID; }

			inline Enums::EComponentType GetCompType() const { return m_componentType; }

			inline bool IsUnique() const { return m_bUnique; }

			virtual void Update() = 0; 

			virtual void DeltaUpdate() = 0;
		};
	}
}