#pragma once

#include <unordered_set>

namespace tf
{
	template<typename T>
	class UnorderedSet : public std::unordered_set<T>
	{
	public:
		using std::unordered_set<T>::unordered_set;

		bool Contains(const T& key) const
		{
			return this->find(key) != this->end();
		}
	};
}