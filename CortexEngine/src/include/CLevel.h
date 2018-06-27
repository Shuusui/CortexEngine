#pragma once
#pragma region Internal includes
#include "ICObject.h"
#include "NamespaceAlias.h"
#pragma endregion
#pragma region External includes
#include <cstdint>
#include <string>
#include <vector>
#pragma endregion

namespace CE
{
	namespace Core
	{
		class CLevel
		{

		private: 
			uint32_t m_objCount; 
			std::string m_name; 
			std::vector<ICObject*> m_objects; 
			uint32_t m_resolutionX; 
			uint32_t m_resolutionY;
			bool m_isDirty;
		public:
			CLevel() = delete; 

			CLevel(const std::string& name, const uint32_t& resolutionX,const uint32_t& resolutionY); 

			inline ICObject* GetCObject(const uint32_t& objIndex) const { return m_objects[objIndex]; }

			void AddObject(CECORE::ICObject* obj);
			
			void RemoveObject(CECORE::ICObject* obj);

			void RemoveObject(const uint32_t& index);

			void Update() { for (ICObject* object : m_objects) { object->Update(); } }

			void Save();

			void Release();

			~CLevel();

			
		private:
		};
	}
}