#include "include\EngineManager.h"

CE::Core::EngineManager* CE::Core::EngineManager::s_pEngineManager = nullptr;
CE::Core::EventHandler* CE::Core::EngineManager::s_pEventHandler = nullptr;
CE::Core::ProjectManager* CE::Core::EngineManager::s_pProjectManager = nullptr;
CE::Editor::CEditor* CE::Core::EngineManager::s_pEditor = nullptr;

CE::Core::EngineParams CE::Core::EngineManager::Init()
{
	EngineParams params;
	//LPWSTR* szArgList;
	//int nArgs;

	//szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	//std::wstring wstr = szArgList[0];
	//for (int i = 0; i < 16; i++)
	//	wstr.pop_back(); 
	//LocalFree(szArgList);
	//
	//params.EnginePath = WStrToStr(wstr);
	//params.hInstance = hInstance;

	if (!InitListener())
		return params; //TODO do some Error Handling here
	
	
	m_pVkRenderer->Init();
	s_pProjectManager = new CE::Core::ProjectManager("project");
	s_pProjectManager->Init();

	return m_pEngineIni->LoadIni(params);
}
//
//bool CE::Core::EngineManager::InitWindow(const EngineParams& params)
//{
//	m_pWndClass = new Window();
//	m_wndHandle = m_pWndClass->Init(params);
//	return m_wndHandle != NULL ? true : false;
//}
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
		try {
			shouldClose = m_pVkRenderer->Run();
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			return;
		}
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