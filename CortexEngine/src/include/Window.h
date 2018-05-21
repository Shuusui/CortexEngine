#pragma once
#pragma region Internal includes
#include "CortexStructs.h"
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
			HWND Init(const EngineParams& params) const;			
			
			void Run(MSG& msg); 

		private:

		};
	}
}