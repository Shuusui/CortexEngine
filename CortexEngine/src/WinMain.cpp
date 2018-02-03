#pragma region Internal includes
#include "include\Window.h"
#include "include\CoreMacros.h"
#pragma endregion
#pragma region External includes
#include <Windows.h>
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WINDOW* currentWindow = new WINDOW();
	currentWindow->Init(1680, 1050, hInstance, nCmdShow);
	delete currentWindow; 
}