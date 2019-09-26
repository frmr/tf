#pragma once

#include <set>

namespace tf
{
	template <typename T>
	class Set : public std::set<T>
	{
	public:
		using std::set<T>::set;

		bool Contains(const T& key) const
		{
			return this->find(key) != this->end();
		}
	};
}