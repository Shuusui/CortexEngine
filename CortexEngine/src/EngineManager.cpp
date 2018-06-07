#include "include\EngineManager.h"

CE::Core::EngineManager* CE::Core::EngineManager::s_pEngineManager = nullptr;
CE::Core::EventHandler* CE::Core::EngineManager::s_pEventHandler = nullptr;
CE::Core::ProjectManager* CE::Core::EngineManager::s_pProjectManager = nullptr;
CE::Editor::CEditor* CE::Core::EngineManager::s_pEditor = nullptr;

CE::Core::EngineParams CE::Core::EngineManager::Init(const HINSTANCE& hInstance)
{
	EngineParams params;
	LPWSTR* szArgList;
	int nArgs;

	szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	std::wstring wstr = szArgList[0];
	for (int i = 0; i < 16; i++)
		wstr.pop_back(); 
	LocalFree(szArgList);
	std::string str;
	_memccpy((void*)str.c_str(), (void*)wstr.c_str(), 0, wstr.size());
	
	params.EnginePath = wstr;
	params.hInstance = hInstance;

	if (!InitListener())
		return params; //TODO do some Error Handling here
		

	return m_pEngineIni->LoadIni(params);
}

bool CE::Core::EngineManager::InitWindow(const EngineParams& params)
{
	m_pWndClass = new Window();
	m_wndHandle = m_pWndClass->Init(params);
	return m_wndHandle != NULL ? true : false;
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
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		m_pWndClass->Run(msg);
		s_pEventHandler->Update();
	}
}

bool CE::Core::EngineManager::CreateNewProject(const std::string & name)
{
	s_pProjectManager = new ProjectManager(name);
	if (!s_pProjectManager)
		return false; 
	ProjectParams params{ 0 };
	params.ProjectName = name;
	return true;
}

bool CE::Core::EngineManager::LoadExistentProject(const std::string & projectFilePath)
{
	return false;
}

void CE::Core::EngineManager::Save()
{

}