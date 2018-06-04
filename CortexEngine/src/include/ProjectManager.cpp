#include "ProjectManager.h"



void CE::Core::ProjectManager::SetInitParams(const ProjectParams & params)
{

}

void CE::Core::ProjectManager::LoadLevel(CLevel * currLevel)
{
}

CE::Core::ProjectManager::ProjectManager(const std::string & name, CLevel* pCurrLevel, const bool& newProj)
	:m_name(name)
	,m_pCurrLevel(pCurrLevel)
{
	if (newProj)
		LoadProjectFile();
}

CE::Core::ProjectManager::~ProjectManager()
{
}

CE::Core::ProjectParams CE::Core::ProjectManager::LoadProjectFile()
{
	ProjectParams params;
	return params;
}


void CE::Core::ProjectManager::Save()
{

}