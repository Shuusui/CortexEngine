#pragma once

#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#pragma endregion 

namespace CortexEngine
{
	namespace Core
	{
		class ProjectManager
		{
		private:
			static ProjectManager* s_pProjectManager;
		public:
			~ProjectManager();
			ProjectManager(const ProjectManager&) = delete;
			static inline bool CreateInstance();
			static inline bool IsInstantiated();
			static inline void Release();
			static inline ProjectManager& GetInstance();
			bool Init();
			void Run();
			bool operator=(const ProjectManager&) = delete;

		private:
			ProjectManager();

		};
	}
}
CortexEngine::Core::ProjectManager* CortexEngine::Core::ProjectManager::s_pProjectManager = nullptr;

CortexEngine::Core::ProjectManager::~ProjectManager()
{
	s_pProjectManager = nullptr; 
}

inline bool CortexEngine::Core::ProjectManager::CreateInstance()
{
	if (!s_pProjectManager)
	{
		ProjectManager();
		return true; 
	}
	return false; 
}

inline bool CortexEngine::Core::ProjectManager::IsInstantiated()
{
	return s_pProjectManager ? true : false; 
}

inline void CortexEngine::Core::ProjectManager::Release()
{
	delete s_pProjectManager; 
}

inline CortexEngine::Core::ProjectManager & CortexEngine::Core::ProjectManager::GetInstance()
{
	return *s_pProjectManager;
}

