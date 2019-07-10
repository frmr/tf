#pragma once

#include <map>

namespace tf
{
	template<typename TKey, typename TValue>
	class Map : public std::map<TKey, TValue>
	{
	public:
		bool Contains(const TKey& key) const
		{
			return this->find(key) != this->end();
		}
	};
}