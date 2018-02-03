#include "include\Level.h"

CortexEngine::Core::Level::Level(const uint32_t& resolutionX, const uint32_t& resolutionY)
{

}

void CortexEngine::Core::Level::AddObject(ICOBJECT* obj)
{
	m_objCount++;
	return false;
}

void CortexEngine::Core::Level::RemoveObject(ICOBJECT* obj)
{
	return false;
}

CortexEngine::Core::Level::~Level()
{

}

