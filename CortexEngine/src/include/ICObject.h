#pragma once
#pragma region Internal includes
#include "Algorithms.h"
#include "Defines.h"
#include "ICComponent.h"
#pragma endregion
#pragma region External includes
#include <cstdint>
#include <string>
#include <vector>
#pragma endregion


namespace CortexEngine
{
	namespace Core
	{
		class ICObject
		{
		private: 
			uint_fast32_t m_ID; 
			std::string m_name;
			uint_fast32_t m_subObjectCount;
			std::vector<ICObject*> m_subObjects;
			std::vector<ICComponent*> m_components;
		public:
			ICObject() = delete;

			ICObject(const uint_fast32_t& id, const std::string& name) : m_ID(id), m_name(name), m_subObjectCount(0) {};

			ICObject(const ICObject& obj) :m_ID(obj.m_ID), m_name(obj.m_name), m_subObjectCount(obj.m_subObjectCount) {}

			inline bool CreateSubobject(const std::string& objName);			

			inline bool AddSubobject(ICObject* obj);
			
			inline bool RemoveSubobject(const uint_fast32_t& id);

			inline bool AddComponent(ICComponent* component);

			inline void RemoveComponent(ICComponent* component);

			inline ICComponent* GetComponent(const uint_fast32_t& id);

			inline uint_fast32_t GetID() const { return m_ID;  }

			inline void SetID(const uint_fast32_t& newId) {m_ID = newId;}

			inline bool operator!=(const ICObject& obj) { return m_ID != obj.m_ID ? true : false; }

			inline bool operator==(const ICObject& obj) { return m_ID == obj.m_ID ? true : false; }

			inline bool operator<(const ICObject& obj) { return m_ID < obj.m_ID ? true : false; }

			inline bool operator>(const ICObject& obj) { return m_ID > obj.m_ID ? true : false; }

			inline bool operator<=(const ICObject& obj) { return m_ID <= obj.m_ID ? true : false; }
			
			inline bool operator>=(const ICObject& obj) { return m_ID >= obj.m_ID ? true : false; }
			
			virtual ~ICObject() {};
		};

		bool ICObject::CreateSubobject(const std::string& objName)
		{
			ICObject* newObj = new ICObject(m_subObjectCount, objName);
			if (!VectorBinSearch(m_subObjects, newObj))
				if (AddSubobject(newObj))
				{
					m_subObjectCount++;
					return true;
				}
			delete newObj;
			return false;
		}

		bool ICObject::AddSubobject(ICObject* obj)
		{
			m_subObjects.push_back(obj);
		}
		inline bool ICObject::RemoveSubobject(const uint_fast32_t & id)
		{
			if (id == m_subObjects[m_subObjects.size()]->GetID())
				m_subObjects.pop_back();
			else
			{
				m_subObjects[id] = m_subObjects[m_subObjects.size()];
				m_subObjects.pop_back();
			}
		}
		inline bool ICObject::AddComponent(ICComponent* component)
		{
			if (component->IsUnique() && VectorBinSearch(m_components, component))
				return false; 
			m_components.push_back(component);
		}

		inline void ICObject::RemoveComponent(ICComponent* component)
		{
			if (component->GetID() == m_components[m_components.size()]->GetID())
				m_components.pop_back();
			
			m_subObjects[component->GetID()] = m_subObjects[m_subObjects.size()]; 
			m_subObjects.pop_back();
		}

		inline ICComponent * ICObject::GetComponent(const uint_fast32_t & id)
		{
			return m_components[id];
		}		
	}
}