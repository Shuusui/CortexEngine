#include "include\Window.h"


///\internal forward declaration of the WindowProc function which is needed for the WindowClassEx.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void const CortexEngine::Core::Window::Init(const uint16_t& resolutionX, const uint16_t& resolutionY, const HINSTANCE& hInstance, const int32_t& nCmdShow)
{
	///\internal Initialize the WNDCLASSEX and set the important things
	WNDCLASSEX wndClass{};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = "Window_Class";
	wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);

	///\internal create a Rectangle to use it for the Window creation. 
	RECT rect{};
	rect.left = 0;
	rect.right = resolutionX;
	rect.top = 0;
	rect.bottom = resolutionY;

	///\internal Adjusts the Window to the left upper corner
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, NULL);

	// registers the current window. 
	RegisterClassEx(&wndClass);

	///\internal Creates the handle of the window 
	HWND hWnd{};
	///\internal Creates the window based on the handle, WNDCLASSEX and the rectangle. 
	hWnd = CreateWindowEx
	(
		NULL,
		wndClass.lpszClassName,
		"GD_Tool",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		nullptr
	);
	///\internal use the run function after the initialization of the Window. 
	Run(hWnd, nCmdShow);
}

void const CortexEngine::Core::Window::Run(const HWND& hWnd, const int32_t& nCmdShow)
{
	///\internal base functions to Show and update the window which was initialized before
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	///\internal the while loop to update the window after a message comes in. 
	while (true)
	{
		if (PeekMessage(&m_message, nullptr, 0, 0, PM_REMOVE))
		{
			if (m_message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&m_message);
			DispatchMessage(&m_message);
		}
	}
}

void const CortexEngine::Core::Window::ShutDown()
{
	///\internal sets manually the message to WM_QUIT. 
	m_message.message = WM_QUIT;
}

CortexEngine::Core::Window::~Window()
{
	ShutDown();
}
///\internal the definition of the forward declared WindowProc method.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	DefWindowProc(hwnd, uMsg, wParam, lParam);
}
