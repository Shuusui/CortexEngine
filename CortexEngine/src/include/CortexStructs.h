#pragma once
#pragma region Internal Includes
#include "Vector3.h"
#pragma endregion 
#pragma region External Includes
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <stb_image.h>
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
			Transform()
				:Position(glm::vec3())
				, Rotation(glm::vec3())
				, Scale(glm::vec3())
			{

			}
			Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3&  scale)
				:Position(pos)
				,Rotation(rot)
				,Scale(scale)
			{
				
			}
			glm::vec3 Position;
			glm::vec3 Rotation; 
			glm::vec3 Scale;
		};
	}
	namespace Rendering
	{
		struct UniformBufferObject {
			glm::mat4 Model;
			glm::mat4 View;
			glm::mat4 Proj;
			glm::mat3 MV3x3;
		};
		struct TexData
		{
			int TexWidth;
			int TexHeight;
			int TexChannels;
			stbi_uc* Pixels;
			void Release()
			{
				stbi_image_free(Pixels);
			}
		};
	}
}