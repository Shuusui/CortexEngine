#include "include\Level.h"

CortexEngine::Core::Level::Level(const uint32_t& resolutionX, const uint32_t& resolutionY)
{

}

void CortexEngine::Core::Level::AddObject(CortexEngine::Core::ICObject* obj)
{
	m_objects.push_back(obj);
	
	m_objCount++;
}

void CortexEngine::Core::Level::RemoveObject(CortexEngine::Core::ICObject* obj)
{

}

void CortexEngine::Core::Level::RemoveObject(const uint32_t & index)
{

}

CortexEngine::Core::Level::~Level()
{

}

