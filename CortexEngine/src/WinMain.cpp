#pragma region Internal includes
#include "include\EngineManager.h"
#pragma endregion
#pragma region External includes
#include <Windows.h>
#include <string>
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (CE::Core::EngineManager::CreateInstance())
		if(CE::Core::EngineManager::GetInstance().InitWindow(CE::Core::EngineManager::GetInstance().Init(hInstance)))
			CE::Core::EngineManager::GetInstance().Run();

}