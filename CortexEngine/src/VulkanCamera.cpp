#include "include/VulkanCamera.h"
#include "include/InternalMacros.h"


CE::Rendering::VulkanCamera::VulkanCamera(VkExtent2D extent, GLFWwindow* window)
	:m_extent(extent)
	,m_pWindow(window)
{
	m_data = {};
	m_data.Position = glm::vec3(0, 0, 0);
	m_data.FoV = 45.0f;
	m_data.Speed = 1.0f; 
	m_data.MouseSpeed = .0005f;
	m_data.Direction = glm::vec3(cos(m_data.VerticalAngle) * sin(m_data.HorizontalAngle),
		sin(m_data.VerticalAngle),
		cos(m_data.VerticalAngle) * cos(m_data.HorizontalAngle));
	m_data.Right = glm::vec3(sin(m_data.HorizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_data.HorizontalAngle - 3.14 / 2.0f));
	m_data.Up = glm::cross(m_data.Right, m_data.Direction);
}

CE::Rendering::VulkanCamera::VulkanCamera(CameraData data, VkExtent2D extent)
	:m_extent(extent)
{

}


void CE::Rendering::VulkanCamera::ResizeExtent(VkExtent2D extent)
{
	m_extent = extent;
}

void CE::Rendering::VulkanCamera::ComputeMatrix(CE::Rendering::UniformBufferObject& ubo)
{
	double xPos, yPos;
	glfwGetCursorPos(m_pWindow, &xPos, &yPos);

	glfwSetCursorPos(m_pWindow, m_extent.width / 2, m_extent.height / 2);

	m_data.HorizontalAngle += m_data.MouseSpeed * TIMEHANDLER->GetDeltaTime() * float(m_extent.width / 2 - xPos);
	m_data.VerticalAngle+= m_data.MouseSpeed * TIMEHANDLER->GetDeltaTime() * float(m_extent.height / 2 - yPos);

	m_data.Direction = glm::vec3(cos(m_data.VerticalAngle) * sin(m_data.HorizontalAngle),
		sin(m_data.VerticalAngle),
		cos(m_data.VerticalAngle) * cos(m_data.HorizontalAngle));
	m_data.Right = glm::vec3(sin(m_data.HorizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_data.HorizontalAngle - 3.14 / 2.0f));
	m_data.Up = glm::cross(m_data.Right, m_data.Direction);

	ubo.Proj = glm::perspective(glm::radians(m_data.FoV), m_extent.width / (float)m_extent.height, 0.1f, 15000.0f);
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

