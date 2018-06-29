#pragma region Internal includes
#include "include\EngineManager.h"
#pragma endregion
#pragma region External includes
//#include <Windows.h>
#include <string>
#pragma endregion


int main()
{
	if (CE::Core::EngineManager::CreateInstance())
		CE::Core::EngineManager::GetInstance().Init();
		CE::Core::EngineManager::GetInstance().Run();
}