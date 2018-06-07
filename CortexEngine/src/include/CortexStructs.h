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
			std::string ProjectFilePath;
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
		struct ChangedVariable
		{
			std::string FilePath; 
			uint_fast32_t Line;
			std::string Change;
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
	namespace Rendering
	{
		struct MeshData
		{

		};
	}
}