#include "ProjectManager.h"



void CE::Core::ProjectManager::SetInitParams(const ProjectParams & params)
{

}

void CE::Core::ProjectManager::LoadLevel(CLevel * currLevel)
{
}

void CE::Core::ProjectManager::NewLevel(const std::string & name, const uint32_t & resX, const uint32_t & resY)
{
	m_pCurrLevel = new CLevel(name, resX, resY);
}

CE::Core::ProjectManager::ProjectManager(const std::string & name, CLevel* pCurrLevel, const bool& newProj)
	:m_name(name)
	,m_pCurrLevel(m_pCurrLevel)
	, m_isDirty(true)
{
	if (!newProj)
		LoadProjectFile();
}

CE::Core::ProjectManager::~ProjectManager()
{
	delete m_pCurrLevel;
}

CE::Core::ProjectParams CE::Core::ProjectManager::LoadProjectFile()
{
	ProjectParams params;
	return params;
}


void CE::Core::ProjectManager::Save()
{

}