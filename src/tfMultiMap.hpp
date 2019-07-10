#pragma once

#include <map>

namespace tf
{
	template<typename TKey, typename TValue>
	class Multimap : public std::multimap<TKey, TValue>
	{
	public:
		using std::multimap<TKey, TValue>::multimap;

		bool Contains(const TKey& key) const
		{
			return this->find(key) != this->end();
		}
	};
}