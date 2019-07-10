#pragma once

#include <queue>

namespace tf
{
	template<typename T>
	class Queue : public std::queue<T>
	{
	};
}