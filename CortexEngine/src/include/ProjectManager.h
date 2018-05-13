#pragma once

#pragma region Internal Includes
#include "CortexStructs.h"
#include "Level.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace CortexEngine
{
	namespace Core
	{
		class ProjectManager
		{
		private:
			static ProjectManager* s_pProjectManager;
			Level* m_pCurrLevel;
			std::string m_name;
		public:
			~ProjectManager();
			ProjectManager(const ProjectManager&) = delete;
			static bool NewProject(const std::string& projectName);
			static bool LoadProject(const std::string& projectPath);
			static ProjectParams LoadProjectFile(const std::string& filePath);
			static inline bool IsInstantiated();
			static void Save();
			static inline void Release();
			static inline ProjectManager& GetInstance();
			void SetInitParams(const ProjectParams& params);
			bool operator=(const ProjectManager&) = delete;
			void LoadLevel(Level* currLevel);
		private:
			ProjectManager(const std::string& name, Level* pCurrLevel = nullptr);
			
		};
	}
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

