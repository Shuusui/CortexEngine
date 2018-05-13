#pragma region Internal includes
#include "include\EngineManager.h"
#pragma endregion
#pragma region External includes
#include <Windows.h>
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CortexEngine::Core::EngineManager::CreateInstance();
	if (CortexEngine::Core::EngineManager::IsInstantiated())
		if (CortexEngine::Core::EngineManager::GetInstance().Init())
			CortexEngine::Core::EngineManager::GetInstance().Run();

}