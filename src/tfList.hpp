#pragma once

#include <list>

namespace tf
{
	template<typename T>
	class List : public std::list<T>
	{
	public:
		bool contains(const T& reference) const
		{
			for (const T& value : *this)
			{
				if (value == reference)
					return true;
			}

			return false;
		}
	};
}