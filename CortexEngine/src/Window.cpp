//#include "include\Window.h"
//#include "include\EngineManager.h"
//#include "include\MouseEvent.h"
//
/////\internal the definition of the forward declared WindowProc method.
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg)
//	{
//	case WM_CLOSE: 
//		DestroyWindow(hwnd); 
//		return 0;
//	case WM_DESTROY:
//		CE::Core::EngineManager::Release();
//		PostQuitMessage(0);
//		return 0;
//	case WM_LBUTTONDOWN: 
//	case WM_RBUTTONDOWN:
//	case WM_MBUTTONDOWN:
//		CE::Core::EngineManager::GetEventHandler()->AddEvent(new CE::Core::MouseEvent(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
//		return 0;
//	}
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//HWND CE::Core::Window::Init(const EngineParams& params) const
//{
//	///\internal Initialize the WNDCLASSEX and set the important things
//	WNDCLASSEX wndClass{};
//	wndClass.cbSize = sizeof(WNDCLASSEX);
//	wndClass.style = CS_HREDRAW | CS_VREDRAW;
//	wndClass.lpfnWndProc = WindowProc;
//	wndClass.hInstance = params.hInstance;
//	wndClass.lpszClassName = "Window_Class";
//	wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
//
//	///\internal create a Rectangle to use it for the Window creation. 
//	RECT rect{};
//	rect.left = 0;
//	rect.right = params.ResX;
//	rect.top = 0;
//	rect.bottom = params.ResY;
//
//	///\internal Adjusts the Window to the left upper corner
//	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, NULL);
//
//	// registers the current window. 
//	RegisterClassEx(&wndClass);
//
//	///\internal Creates the handle of the window 
//	HWND hWnd{};
//	///\internal Creates the window based on the handle, WNDCLASSEX and the rectangle. 
//	hWnd = CreateWindowEx
//	(
//		NULL,
//		wndClass.lpszClassName,
//		"GD_Tool",
//		WS_OVERLAPPEDWINDOW,
//		0,
//		0,
//		rect.right - rect.left,
//		rect.bottom - rect.top,
//		NULL,
//		NULL,
//		params.hInstance,
//		nullptr
//	);
//	///\internal use the run function after the initialization of the Window. 
//	ShowWindow(hWnd, SW_SHOW);
//	UpdateWindow(hWnd);
//	return hWnd;
//}
//
//void CE::Core::Window::Run(MSG & msg)
//{
//	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
//	{
//		TranslateMessage(&msg); 
//		DispatchMessage(&msg);
//	}
//
//}
//
