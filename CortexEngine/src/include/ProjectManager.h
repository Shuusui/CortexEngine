#pragma once

#pragma region Internal Includes
#include "CortexStructs.h"
#include "Level.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class ProjectManager
		{
		private:
			Level* m_pCurrLevel;
			std::string m_name;
		public:
			ProjectManager(const std::string& name, Level* pCurrLevel = nullptr, const bool& newProj = true);
			ProjectManager(const ProjectManager&) = delete;
			~ProjectManager();
			ProjectParams LoadProjectFile();
			void Save();
			void SetInitParams(const ProjectParams& params);
			bool operator=(const ProjectManager&) = delete;
			void LoadLevel(Level* currLevel);
		private:
			
		};
	}
}

