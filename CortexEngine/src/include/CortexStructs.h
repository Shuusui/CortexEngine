#pragma once
#pragma region Internal Includes
#include "Vector3.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <Windows.h>
#pragma endregion 

namespace CortexEngine
{
	namespace Core
	{
		struct ProjectParams
		{
			std::string ProjectName;
		};
		struct Transform
		{
			Nash::FVector3 Position;
			Nash::FVector3 Scale;
		};
		struct EngineParams
		{
			std::wstring EnginePath;
			uint16_t ResX; 
			uint16_t ResY; 
			HINSTANCE hInstance;
		};
	}
}