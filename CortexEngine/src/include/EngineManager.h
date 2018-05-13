#pragma once
#pragma region Internal Includes
#include "ProjectManager.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <fstream>
#pragma endregion 


namespace CortexEngine
{
	namespace Core
	{
		class EngineManager
		{
		private: 
			static EngineManager* s_pEngineManager;
		public: 
			~EngineManager() {	s_pEngineManager = nullptr;	};
			EngineManager(const EngineManager&) = delete; 
			static inline bool CreateInstance(); 
			static inline bool IsInstantiated(); 
			static inline EngineManager& GetInstance(); 
			static inline void Release(); 
			static void Save();
			bool Init(); 
			void LoadIni();
			void CreateDefaultIni();
			void SetDefaultSettings();
			void Run();
			bool operator=(const EngineManager&) = delete; 
		private: 
			EngineManager() { s_pEngineManager = this; };
			

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




