#include "include\EngineManager.h"

CE::Core::EngineManager* CE::Core::EngineManager::s_pEngineManager = nullptr;
CE::Core::EventHandler* CE::Core::EngineManager::s_pEventHandler = nullptr;
CE::Core::ProjectManager* CE::Core::EngineManager::s_pProjectManager = nullptr;
CE::Core::TimeHandler* CE::Core::EngineManager::s_pTimeHandler = nullptr;

CE::Core::EngineParams CE::Core::EngineManager::Init()
{
	EngineParams params;

	if (!InitListener())
		return params; //TODO do some Error Handling here
	
	s_pTimeHandler = new CE::Core::TimeHandler();
	m_pVkRenderer->InitDevices();
	s_pProjectManager = new CE::Core::ProjectManager("project");
	s_pProjectManager->Init();
	m_pVkRenderer->Init();

	return m_pEngineIni->LoadIni(params);
}

bool CE::Core::EngineManager::InitListener()
{
	Console* console = new Console();
	if (!console)
		return false; 
	DirtyEventListener* dirtyListener = new DirtyEventListener();
	if (!dirtyListener)
		return false; 
	s_pEventHandler->RegisterListener(console);
	s_pEventHandler->RegisterListener(dirtyListener);
	return true;
}
void CE::Core::EngineManager::Run()
{
	int shouldClose = 0;
	while (!shouldClose)
	{
		s_pTimeHandler->Update();
		try {
			shouldClose = m_pVkRenderer->Run();
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			return;
		}
		s_pProjectManager->Update();
		s_pEventHandler->Update();
	}
	EngineManager::Release();
}

bool CE::Core::EngineManager::CreateNewProject(const std::string & name)
{

	s_pProjectManager = new ProjectManager(name);
	if (!s_pProjectManager)
		return false; 
	ProjectParams params{ 0 };
	params.ProjectName = name;
	params.ProjectFilePath = m_pEngineIni->GetParams().EnginePath + "//" + name;
	s_pProjectManager->SetInitParams(params);
	if (!s_pProjectManager->Init())
		return false;
	return true;
}

bool CE::Core::EngineManager::LoadExistentProject(const std::string & projectFilePath)
{
	return false;
}

void CE::Core::EngineManager::Save()
{

}