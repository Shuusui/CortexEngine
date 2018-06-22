#include "include\CLevel.h"

CE::Core::CLevel::CLevel(const std::string& name, const uint32_t& resolutionX, const uint32_t& resolutionY)
	:m_name(name)
	,m_resolutionX(resolutionX)
	,m_resolutionY(resolutionY)
	,m_isDirty(false)
{

}

void CE::Core::CLevel::AddObject(CECORE::ICObject* obj)
{
	m_objects.push_back(obj);
	
	m_objCount++;
}

void CE::Core::CLevel::RemoveObject(CECORE::ICObject* obj)
{

}

void CE::Core::CLevel::RemoveObject(const uint32_t & index)
{

}

void CE::Core::CLevel::Save()
{

}

CE::Core::CLevel::~CLevel()
{
	for (const auto& object : m_objects)
	{
		delete(object);
	}
}

