#include "ProjectManager.h"



void CortexEngine::Core::ProjectManager::SetInitParams(const ProjectParams & params)
{

}

void CortexEngine::Core::ProjectManager::LoadLevel(Level * currLevel)
{
}

CortexEngine::Core::ProjectManager::ProjectManager(const std::string & name, Level* pCurrLevel, const bool& NewProj)
	:m_name(name)
	,m_pCurrLevel(pCurrLevel)
{
	if (NewProj)
		LoadProjectFile();
}

CortexEngine::Core::ProjectManager::~ProjectManager()
{
}

CortexEngine::Core::ProjectParams CortexEngine::Core::ProjectManager::LoadProjectFile()
{
	ProjectParams params;
	return params;
}


void CortexEngine::Core::ProjectManager::Save()
{

}