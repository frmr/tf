#pragma once

#include <unordered_map>
#include "tfUnorderedSet.hpp"

namespace tf
{
	template<typename TKey, typename TValue>
	class UnorderedMap : public std::unordered_map<TKey, TValue>
	{
	public:
		using std::unordered_map<TKey, TValue>::unordered_map;

		bool contains(const TKey& key) const
		{
			return this->find(key) != this->end();
		}

		tf::UnorderedSet<TKey> getKeys() const
		{
			UnorderedSet<TKey> keys;

			keys.reserve(this->size());

			for (const auto pair : *this)
			{
				keys.insert(pair.first);
			}

			return keys;
		}
	};
}