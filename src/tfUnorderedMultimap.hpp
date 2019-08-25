#pragma once

#include <unordered_map>
#include "tfVector.hpp"

namespace tf
{
	template<typename TKey, typename TValue>
	class UnorderedMultimap : public std::unordered_multimap<TKey, TValue>
	{
	public:
		using std::unordered_multimap<TKey, TValue>::unordered_multimap;

		bool contains(const TKey& key) const
		{
			return this->find(key) != this->end();
		}

		Vector<TValue> getValues(const TKey& key) const
		{
			Vector<TValue> values;

			const auto range = this->equal_range(key);

			for (auto it = range.first; it != range.second; ++it)
			{
				values.push_back(it->second);
			}

			return values;
		}
	};
}