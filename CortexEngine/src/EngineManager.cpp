#include "include\EngineManager.h"

CE::Core::EngineManager* CE::Core::EngineManager::s_pEngineManager = nullptr;
CE::Core::EventHandler* CE::Core::EngineManager::s_pEventHandler = nullptr;
CE::Core::ProjectManager* CE::Core::EngineManager::s_pProjectManager = nullptr;

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
	params.EnginePath = wstr; 
	params.hInstance = hInstance;

	Console* console = new Console(); 
	s_pEventHandler->RegisterListener(console);

	return m_pEngineIni->LoadIni(params);
}

bool CE::Core::EngineManager::InitWindow(const EngineParams& params)
{
	m_pWndClass = new Window();
	m_wndHandle =  m_pWndClass->Init(params);
	return m_wndHandle != NULL ? true : false;
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

void CE::Core::EngineManager::Save()
{

}