#pragma once
#pragma region Internal Includes
#include "CortexStructs.h"
#pragma endregion 
#pragma region External Includes
#include <string> 
#include <fstream> //fstream etc.
#include <cstdlib> // wcstombs
#pragma endregion 

namespace CE
{
	namespace Core
	{
		class EngineIni
		{
		private:
			EngineParams m_engineParams;
		public:
			EngineIni(const std::string& enginePath)
			{

			}
			EngineParams LoadIni(EngineParams& params);
			EngineParams GetParams() const { return m_engineParams; }
		private: 
			EngineParams CreateDefaultIni(EngineParams& params);
		};
	}
}