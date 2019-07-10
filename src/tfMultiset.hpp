#pragma once

#include <set>

namespace tf
{
	template<typename T>
	class Multiset : public std::multiset<T>
	{
	public:
		using std::multiset<T>::multiset;

		bool Contains(const T& key) const
		{
			return this->find(key) != this->end();
		}
	};
}