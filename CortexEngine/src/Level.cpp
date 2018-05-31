#include "include\Level.h"

CE::Core::Level::Level(const uint32_t& resolutionX, const uint32_t& resolutionY)
{

}

void CE::Core::Level::AddObject(CECORE::ICObject* obj)
{
	m_objects.push_back(obj);
	
	m_objCount++;
}

void CE::Core::Level::RemoveObject(CECORE::ICObject* obj)
{

}

void CE::Core::Level::RemoveObject(const uint32_t & index)
{

}

CE::Core::Level::~Level()
{

}

