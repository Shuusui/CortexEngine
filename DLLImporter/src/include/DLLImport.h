#pragma once

#pragma region External Includes
#include <string>
#include <fstream>
#include <Shlwapi.h>
#pragma endregion 


namespace DLLImporter
{
	static void ImportDLL(const std::string& includePath, const std::string& libPath, const std::string& projectPath)
	{
		HANDLE hFile; 		
		WIN32_FIND_DATA fileInfo;
		std::string strPattern = includePath + "\\*.*"; 
		hFile = ::FindFirstFile(strPattern.c_str(), &fileInfo);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (fileInfo.cFileName[0] != '.')
				{

				}
			} while (::FindNextFile(hFile, &fileInfo) == TRUE);

			::FindClose(hFile);
		}
	}
	static bool CheckData(const std::string& includePath, const std::string& libPath, const std::string& projectPath)
	{

	}
}