#pragma once
#pragma region Internal includes
#include "ICObject.h"
#pragma endregion
#pragma region External includes
#include <cstdint>
#pragma endregion


static uint_fast64_t m_objCount; 

namespace CortexEngine
{
	namespace Core
	{
		class Level
		{

		public:
			Level(const uint32_t& resolutionX,const uint32_t& resolutionY); 

			void AddObject(CortexEngine::Core::ICObject* obj);
			
			void RemoveObject(CortexEngine::Core::ICObject* obj);

			~Level();
		private:
		};
	}
}