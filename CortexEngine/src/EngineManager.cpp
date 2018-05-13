#include "include\EngineManager.h"

CortexEngine::Core::EngineManager* CortexEngine::Core::EngineManager::s_pEngineManager = nullptr;


bool CortexEngine::Core::EngineManager::Init()
{
	
	return true;
}

void CortexEngine::Core::EngineManager::LoadIni()
{
	std::fstream iniStream;
	iniStream.open("engine.ini",std::ios::in); 
	if (iniStream.is_open())
	{

	}
	else
		CreateDefaultIni();

	iniStream.close();
}

void CortexEngine::Core::EngineManager::CreateDefaultIni()
{
	std::fstream defaultStream; 
	defaultStream.open("engine.ini", std::ios::out);
	if (defaultStream.is_open())
	{

	}
	defaultStream.close();
	SetDefaultSettings();
}


void CortexEngine::Core::EngineManager::SetDefaultSettings()
{

}

void CortexEngine::Core::EngineManager::Run()
{
	while (true)
	{

	}
}

void CortexEngine::Core::EngineManager::Save()
{

}