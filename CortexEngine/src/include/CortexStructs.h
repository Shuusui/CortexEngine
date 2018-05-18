#pragma once
#pragma region Internal Includes
#include "Vector3.h"
#include "Quaternion.h"
#pragma endregion 
#pragma region External Includes
#include <string>
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
			Nash::Quaternion Rotation;
			Nash::FVector3 Scale;
		};
	}
}