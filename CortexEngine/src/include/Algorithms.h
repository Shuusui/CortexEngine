#pragma once
#pragma region External Includes
#include <vector>
#include <string>
#include <Windows.h>
#pragma endregion

namespace CE
{
	namespace Core
	{
		/**
		* Binary search for vectors. Only works with comparable key values
		*
		* @param container The container you want to search in
		* @param keyVal The key value you want to search in the container
		* @result Returns true if it's found or false if it's not found
		*/
		template <typename t1, typename t2>
		static bool VectorBinSearch(const std::vector<t1>& container, const t2& keyVal)
		{
			if (keyVal < container[container.size() / 2])
			{
				for (size_t i = container.size() / 2; i >= 0; i--)
				{
					if (keyVal == container[i])
						return true;
				}
				return false;
			}
			else
			{
				for (size_t i = container.size() / 2; i < container.size(); i++)
				{
					if (keyVal == container[i])
						return true;
				}
				return false;
			}
		}

		static std::string WStrToStr(const std::wstring& wstr)
		{
			int len;
			len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), 0, 0, 0, 0);
			std::string str(len, '\0');
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), &str[0], len, 0, 0);
			return str;
		}
	}
}