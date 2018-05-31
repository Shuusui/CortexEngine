#pragma once
#pragma region Internal Includes
#include "Vector3.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <Windows.h>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		struct ProjectParams
		{
			std::string ProjectName;
		};
		struct EngineParams
		{
			std::wstring EnginePath;
			uint16_t ResX; 
			uint16_t ResY; 
			HINSTANCE hInstance;
		};
		struct FBXData
		{
			Nash::FVector3 Pos;
		};
	}
	namespace Physics
	{
		struct Transform
		{
			Nash::FVector3 Position;
			Nash::FVector3 Scale;
		};

	}
}