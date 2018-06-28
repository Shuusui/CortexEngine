#include "include/VulkanCamera.h"
#include "include/InternalMacros.h"


CE::Rendering::VulkanCamera::VulkanCamera(VkExtent2D extent)
	:m_extents(extent)
{
	m_data = {};
	m_data.Position = glm::vec3(0, 0, 0);
	m_data.FoV = 45.0f;
	m_data.Speed = 1.0f; 
	m_data.MouseSpeed = .005f;
	m_data.Direction = glm::vec3(cos(m_data.VerticalAngle) * sin(m_data.HorizontalAngle),
		sin(m_data.VerticalAngle),
		cos(m_data.VerticalAngle) * cos(m_data.HorizontalAngle));
	m_data.Right = glm::vec3(sin(m_data.HorizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_data.HorizontalAngle - 3.14 / 2.0f));
	m_data.Up = glm::cross(m_data.Right, m_data.Direction);
}

CE::Rendering::VulkanCamera::VulkanCamera(CameraData data, VkExtent2D extent)
	:m_extents(extent)
{

}


void CE::Rendering::VulkanCamera::ResizeExtent(VkExtent2D extent)
{
	m_extents = extent;
}

void CE::Rendering::VulkanCamera::ComputeMatrix(CE::Rendering::UniformBufferObject& ubo)
{
	ubo.Proj = glm::perspective(glm::radians(m_data.FoV), m_extents.width / (float)m_extents.height, 0.1f, 500.0f);
	ubo.View = glm::lookAt(m_data.Position, m_data.Position + m_data.Direction, m_data.Up);
}

void CE::Rendering::VulkanCamera::Move(Enums::EDirection dir)
{
	switch (dir)
	{
	case Enums::EDirection::Forward:
		m_data.Position += m_data.Direction * TIMEHANDLER->GetDeltaTime() * m_data.Speed;
		break;
	case Enums::EDirection::Backward:
		m_data.Position -= m_data.Direction * TIMEHANDLER->GetDeltaTime() * m_data.Speed;
		break;
	case Enums::EDirection::Left:
		m_data.Position -= m_data.Right * TIMEHANDLER->GetDeltaTime() * m_data.Speed;
		break;
	case Enums::EDirection::Right:
		m_data.Position += m_data.Right * TIMEHANDLER->GetDeltaTime() * m_data.Speed;
		break;
	}
}

