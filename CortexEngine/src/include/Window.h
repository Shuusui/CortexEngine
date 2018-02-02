#pragma once

#pragma region Internal includes
#pragma endregion
#pragma region External includes
#include <Windows.h>
#pragma endregion

namespace CortexEngine
{
	namespace Core
	{
		class Window
		{
		public:
			/**
			* The Default Constructor of the Window class to initialize a new Window
			*
			*/
			Window(); 
			/**
			* The Initialize method of the current window. 
			*/
			void Init(); 
			/**
			* The Run function fo the current Window. There will be the core loop to hold the window open. 
			*/
			void Run(); 
			/**
			* The Destrox method of the current window to shut down the window manually
			*/
			void Destroy();
			/**
			* The default Destructor of the current window class to safe delete the class
			*/
			~Window(); 
		};
	}
}