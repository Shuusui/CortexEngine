#include "include\EngineManager.h"

CortexEngine::Core::EngineManager* CortexEngine::Core::EngineManager::s_pEngineManager = nullptr;


CortexEngine::Core::EngineParams CortexEngine::Core::EngineManager::Init(const HINSTANCE& hInstance)
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
	return m_pEngineIni->LoadIni(params);
}

bool CortexEngine::Core::EngineManager::InitWindow(const EngineParams& params)
{
	m_pWndClass = new Window();
	m_wndHandle =  m_pWndClass->Init(params);
	return m_wndHandle != NULL ? true : false;
}
void CortexEngine::Core::EngineManager::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		m_pWndClass->Run(msg);
	}
}

void CortexEngine::Core::EngineManager::Save()
{

}