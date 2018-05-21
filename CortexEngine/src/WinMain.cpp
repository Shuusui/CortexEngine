#pragma region Internal includes
#include "include\EngineManager.h"
#pragma endregion
#pragma region External includes
#include <Windows.h>
#include <string>
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (CortexEngine::Core::EngineManager::CreateInstance())
		if(CortexEngine::Core::EngineManager::GetInstance().InitWindow(CortexEngine::Core::EngineManager::GetInstance().Init(hInstance)))
			CortexEngine::Core::EngineManager::GetInstance().Run();

}