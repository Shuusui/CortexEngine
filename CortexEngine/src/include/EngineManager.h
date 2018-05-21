#pragma once
#pragma region Internal Includes
#include "ProjectManager.h"
#include "CortexStructs.h"
#include "EngineIni.h"
#include "Window.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 


namespace CortexEngine
{
	namespace Core
	{
		class EngineManager
		{
		private: 
			static ProjectManager* s_pProjectManager;
			static EngineManager* s_pEngineManager;
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
			EngineParams Init(const HINSTANCE& hInstance);
			bool InitWindow(const EngineParams& params);			
			void Run();
			bool operator=(const EngineManager&) = delete; 
		private: 
			EngineManager() 
				
			{ 
				s_pEngineManager = this;
				m_pEngineIni = new EngineIni("");
			};
			

		};
	}
}


bool CortexEngine::Core::EngineManager::CreateInstance()
{
	if (!s_pEngineManager)
	{
		s_pEngineManager = new EngineManager();
		return true; 
	}
	return false; 
}

bool CortexEngine::Core::EngineManager::IsInstantiated()
{
	return s_pEngineManager ? true : false; 
}

CortexEngine::Core::EngineManager& CortexEngine::Core::EngineManager::GetInstance()
{
	return *s_pEngineManager;
}


void CortexEngine::Core::EngineManager::Release()
{
	delete s_pEngineManager; 
}




