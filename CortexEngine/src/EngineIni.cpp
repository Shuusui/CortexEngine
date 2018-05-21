#include "include\EngineIni.h"

CortexEngine::Core::EngineParams CortexEngine::Core::EngineIni::LoadIni(EngineParams& params)
{
	std::fstream iniStream;
	iniStream.open("engine.ini", std::ios::in);
	if (!iniStream.is_open())
	{
		return CreateDefaultIni(params);
	}
	int lineCount = 0;
	iniStream.seekg(0, iniStream.end);
	size_t size = iniStream.tellg();
	iniStream.seekg(0, iniStream.beg);
	char* buffer = (char*)malloc(size); 
	while (!iniStream.eof())
	{
		iniStream.getline(buffer, size);
		if (lineCount == 0)
		{
			params.ResX = atoi(buffer);
		}
		if (lineCount == 1)
		{
			params.ResY = atoi(buffer);
		}
		lineCount++;
	}
	return params;
}

CortexEngine::Core::EngineParams CortexEngine::Core::EngineIni::CreateDefaultIni(EngineParams& params)
{
	std::fstream defaultStream;
	defaultStream.open("engine.ini", std::ios::out);
	params.ResX = 1024; 
	params.ResY = 768; 
	std::string buffer; 
	if (defaultStream.is_open())
	{
		buffer.append(std::to_string(params.ResX) + "\n");
		buffer.append(std::to_string(params.ResY) + "\n");
		defaultStream.write(buffer.c_str(),buffer.size());
		defaultStream.close();
	}
	return params;
}
