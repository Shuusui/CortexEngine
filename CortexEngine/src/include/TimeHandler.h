#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/vec3.hpp>
#pragma endregion 


namespace CE
{
	namespace Core
	{
		class TimeHandler
		{
		private: 
			double m_initTime;
			float m_deltaTime;
			double m_lastTime;
		public:
			TimeHandler();

			~TimeHandler();

			void Update();

			float GetDeltaTime();
		};
	}
}