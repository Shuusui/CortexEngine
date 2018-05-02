#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
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
			~EngineManager();
			EngineManager(const EngineManager&) = delete; 
			static inline bool CreateInstance(); 
			static inline bool IsInstantiated(); 
			static inline EngineManager& GetInstance(); 
			static inline void Release(); 
			bool Init(); 
			void Run();
			bool operator=(const EngineManager&) = delete; 
		private: 
			EngineManager(); 
			

		};
	}
}
CortexEngine::Core::EngineManager* CortexEngine::Core::EngineManager::s_pEngineManager = nullptr;

CortexEngine::Core::EngineManager::EngineManager()
{
	s_pEngineManager = this; 
}

bool CortexEngine::Core::EngineManager::CreateInstance()
{
	if (!s_pEngineManager)
	{
		EngineManager();
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

CortexEngine::Core::EngineManager::~EngineManager()
{
	s_pEngineManager = nullptr; 
}

void CortexEngine::Core::EngineManager::Release()
{
	delete s_pEngineManager; 
}


