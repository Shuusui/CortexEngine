#pragma once
#pragma region Internal Includes
#include "ProjectManager.h"
#include "CortexStructs.h"
#include "EngineIni.h"
#include "Window.h"
#include "EventHandler.h"
#include "Console.h"
#include "MessageEvent.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 


namespace CE
{
	namespace Core
	{
		class EngineManager
		{
		private: 
			static EngineManager* s_pEngineManager;
			static ProjectManager* s_pProjectManager;
			static EventHandler* s_pEventHandler;
			EngineIni* m_pEngineIni;
			Window* m_pWndClass;
			HWND m_wndHandle;
		public: 
			~EngineManager() {	s_pEngineManager = nullptr;	};
			EngineManager(const EngineManager&) = delete; 
			static inline bool CreateInstance(); 
			static inline bool IsInstantiated(); 
			static inline EngineManager& GetInstance(); 
			static inline void Release(); 
			static void Save();
			static ProjectManager* GetProjManager() { return s_pProjectManager; }
			static EventHandler* GetEventHandler() { return s_pEventHandler; }
			EngineParams Init(const HINSTANCE& hInstance);
			bool InitWindow(const EngineParams& params);			
			void Run();
			bool operator=(const EngineManager&) = delete; 
		private: 
			EngineManager() 
			{ 
				s_pEngineManager = this;
				m_pEngineIni = new EngineIni("");
				s_pEventHandler = new EventHandler();
			};			
		};
	}
}


bool CE::Core::EngineManager::CreateInstance()
{
	if (!s_pEngineManager)
	{
		s_pEngineManager = new EngineManager();
		MessageEvent* msgE = new MessageEvent("Engine successfully instantiated");
		return true; 
	}
	MessageEvent* msgE = new MessageEvent("Engine couldn't be instantiated");
	return false; 
}

bool CE::Core::EngineManager::IsInstantiated()
{
	return s_pEngineManager ? true : false; 
}

CE::Core::EngineManager& CE::Core::EngineManager::GetInstance()
{
	return *s_pEngineManager;
}


void CE::Core::EngineManager::Release()
{
	delete s_pEventHandler; 
	delete s_pProjectManager;
	delete s_pEngineManager;
}




