#include "include\Level.h"

CortexEngine::Core::Level::Level(const uint32_t& resolutionX, const uint32_t& resolutionY)
{

}

void CortexEngine::Core::Level::AddObject(CortexEngine::Core::ICObject* obj)
{
	m_objCount++;
}

void CortexEngine::Core::Level::RemoveObject(CortexEngine::Core::ICObject* obj)
{
}

CortexEngine::Core::Level::~Level()
{

}

