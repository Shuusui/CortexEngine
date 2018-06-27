#include "include/TimeHandler.h"

CE::Core::TimeHandler::TimeHandler()
	:m_initTime(glfwGetTime())
	,m_deltaTime(0)
	,m_lastTime(glfwGetTime())
{
}

CE::Core::TimeHandler::~TimeHandler()
{
}

void CE::Core::TimeHandler::Update()
{
	double currentTime = glfwGetTime();
	m_deltaTime = float(currentTime - m_lastTime);
}

float CE::Core::TimeHandler::GetDeltaTime()
{
	return m_deltaTime;
}
