#pragma once
#pragma region Internal Includes
#include "Vector3.h"
#pragma endregion 
#pragma region External Includes
#include <glm/vec3.hpp>
#include <string>
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
			std::string EnginePath;
			uint16_t ResX; 
			uint16_t ResY; 
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
			Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3&  scale)
			{

			}
			glm::vec3 Position;
			glm::vec3 Rotation; 
			glm::vec3 Scale;
		};
	}
	namespace Rendering
	{
		struct MeshData
		{

		};
	}
}