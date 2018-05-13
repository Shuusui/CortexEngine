#pragma once

#pragma region External Includes
#include <vector>
#pragma endregion

namespace CortexEngine
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
			if (keyVal < container[container.size / 2])
			{
				for (int i = container.size() / 2; i >= 0; i--)
				{
					if (keyVal == container[i])
						return true;
				}
				return false;
			}
			else
			{
				for (int i = container.size() / 2; i < container.size(); i++)
				{
					if (keyVal == container[i])
						return true;
				}
				return false;
			}
		}
	}
}