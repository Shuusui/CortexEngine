#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#include "Enums.h"
#pragma endregion 
#pragma region External Includes
#include <math.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#pragma endregion 

namespace CE
{
	namespace Rendering
	{
		struct CameraData
		{
			glm::vec3 Position;
			glm::vec3 Direction;
			glm::vec3 Up;
			glm::vec3 Right;
			float FoV; 
			float HorizontalAngle; 
			float VerticalAngle;
			float Speed;
			float MouseSpeed;
		};


		class VulkanCamera
		{
		private: 
			CameraData m_data;
			VkExtent2D m_extents;
		public: 
			VulkanCamera(VkExtent2D extent);
			VulkanCamera(CameraData data, VkExtent2D extent);
			void ResizeExtent(VkExtent2D extent);
			void ComputeMatrix(CE::Rendering::UniformBufferObject& ubo);
			void Move(Enums::EDirection& dir);
		};
	}
}