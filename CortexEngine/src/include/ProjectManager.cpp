#include "ProjectManager.h"

CortexEngine::Core::ProjectManager* CortexEngine::Core::ProjectManager::s_pProjectManager = nullptr;


void CortexEngine::Core::ProjectManager::SetInitParams(const ProjectParams & params)
{

}

void CortexEngine::Core::ProjectManager::LoadLevel(Level * currLevel)
{
}

CortexEngine::Core::ProjectManager::ProjectManager(const std::string & name, Level* pCurrLevel)
	:m_name(name)
	,m_pCurrLevel(pCurrLevel)
{
	s_pProjectManager = this;
}

CortexEngine::Core::ProjectManager::~ProjectManager()
{
	s_pProjectManager = nullptr;
}

bool CortexEngine::Core::ProjectManager::NewProject(const std::string & projectName)
{
	if (!s_pProjectManager)
	{
		s_pProjectManager = new ProjectManager(projectName);
		return true;
	}
	return false;

}

bool CortexEngine::Core::ProjectManager::LoadProject(const std::string & projectPath)
{
	if (!s_pProjectManager)
	{
		ProjectParams params = LoadProjectFile(projectPath);
		s_pProjectManager = new ProjectManager(params.ProjectName);
		s_pProjectManager->SetInitParams(params);
		return true;
	}
	return false;
}

CortexEngine::Core::ProjectParams CortexEngine::Core::ProjectManager::LoadProjectFile(const std::string & filePath)
{
	ProjectParams params;
	return params;
}


void CortexEngine::Core::ProjectManager::Save()
{

}