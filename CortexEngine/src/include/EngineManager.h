#pragma once
#pragma region Internal Includes
#include "ProjectManager.h"
#include "CortexStructs.h"
#include "EngineIni.h"
#include "Window.h"
#include "EventHandler.h"
#include "Console.h"
#include "MessageEvent.h"
#include "CEditor.h"
#include "DirtyEventListener.h"
#include "Algorithms.h"
#include "VulkanRenderer.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <memory.h>
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
			static Editor::CEditor* s_pEditor;
			EngineIni* m_pEngineIni;
			//Window* m_pWndClass;
			//HWND m_wndHandle;
			Rendering::VulkanRenderer* m_pVkRenderer;
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
			static Editor::CEditor* GetEditor() { return s_pEditor; }
			EngineParams Init();
			//bool InitWindow(const EngineParams& params);
			bool InitListener();
			void Run();
			bool CreateNewProject(const std::string& name);
			bool LoadExistentProject(const std::string& projectFilePath);
			bool operator=(const EngineManager&) = delete; 
		private: 
			EngineManager() 
			{ 
				s_pEngineManager = this;
				m_pEngineIni = new EngineIni("");
				s_pEventHandler = new EventHandler();
				s_pEditor = new Editor::CEditor();
				m_pVkRenderer = new Rendering::VulkanRenderer();
			};			
		};
	}
}


bool CE::Core::EngineManager::CreateInstance()
{
	if (!s_pEngineManager)
	{
		s_pEngineManager = new EngineManager();
		MessageEvent* msgE = new MessageEvent("Engine successfully instantiated \n");
		return true; 
	}
	MessageEvent* msgE = new MessageEvent("Engine couldn't be instantiated \n");
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
	s_pEngineManager->m_pVkRenderer->Release();
	delete s_pEventHandler; 
	delete s_pProjectManager;
	delete s_pEngineManager;
	delete s_pEditor;
}




