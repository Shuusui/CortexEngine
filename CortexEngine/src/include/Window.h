#pragma once

#pragma region Internal includes
#pragma endregion
#pragma region External includes
#include <Windows.h>
#include <cstdint>
#pragma endregion

namespace CortexEngine
{
	namespace Core
	{
		///\class Window.h "src/include/Window.h
		///\brief this is the base window class which creates an window. 
		class Window
		{
		public:
			/**
			* The Default Constructor of the window
			*/
			Window() {};
			/**
			* The Copy Constructor of the window class
			*/
			Window(const Window& window) {};
			/**
			*Initialize the window
			*
			* @param resolutionX The Resolution of the X axis from the current window
			* @param resolutionY The Resolution of the Y axis from the current window
			* @param hInstance The handle of the current instance
			* @param nCmdShow The command of the current window to specialize how the window will be displayed
			*/
			void const Init(const uint16_t& resolutionX, const uint16_t& resolutionY, const HINSTANCE& hInstance, const int32_t& nCmdShow);
			/**
			*Shut down the current window
			*/
			void const ShutDown();
			/**
			* Destructor
			*/
			~Window();
		private:
			/**
			* the private run function which will get started after the window is initialized.
			* @param hWnd The handle of the current window which is initialized in the Init() function
			* @param nCmdShow The command of the current window hand over from the Init() method.
			*/
			void const Run(const HWND& hWnd, const int32_t& nCmdShow);
			/**
			* private member variable of a MSG to set the message to WM_QUIT in the shut down and the run function.
			*/
			MSG m_message;

		};
	}
}