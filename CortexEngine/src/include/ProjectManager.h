#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#include "CLevel.h"
#include "ICObject.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class ProjectManager
		{
		private:
			CLevel* m_pCurrLevel;
			std::string m_name;
			bool m_isDirty;
		public:
			ProjectManager(const std::string& name, CLevel* pCurrLevel = nullptr, const bool& newProj = true);
			ProjectManager(const ProjectManager&) = delete;
			~ProjectManager();
			static ProjectParams LoadProjectFile();
			bool Init();
			void Save();
			void SetInitParams(const ProjectParams& params);
			bool operator=(const ProjectManager&) = delete;
			void LoadLevel(CLevel* currLevel);
			void NewLevel(const std::string& name, const uint32_t& resX, const uint32_t& resY);
			CLevel* Level() { return m_pCurrLevel; }
		private:
			
		};
	}
}

