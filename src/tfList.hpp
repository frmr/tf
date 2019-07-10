#pragma once

#include <list>

namespace tf
{
	template<typename T>
	class List : public std::list<T>
	{
	public:
		bool Contains(const T& reference) const
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