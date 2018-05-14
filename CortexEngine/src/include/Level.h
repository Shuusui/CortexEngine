#pragma once
#pragma region Internal includes
#include "ICObject.h"
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

		class Level
		{

		private: 
			uint32_t m_objCount; 
			std::string m_name; 
			std::vector<ICObject*> m_objects; 
		public:
			Level() = delete; 

			Level(const uint32_t& resolutionX,const uint32_t& resolutionY); 

			inline ICObject* GetObject(const uint32_t& objIndex) const { return m_objects[objIndex]; }

			void AddObject(CortexEngine::Core::ICObject* obj);
			
			void RemoveObject(CortexEngine::Core::ICObject* obj);

			void RemoveObject(const uint32_t& index);

			~Level();

			
		private:
		};
	}
}