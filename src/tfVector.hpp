#pragma once

#include <vector>

namespace tf
{
	template<typename T>
	class Vector : public std::vector<T>
	{
	public:
		using std::vector<T>::vector;

		void Append(const Vector<T>& other)
		{
			insert(this->end(), other.begin(), other.end());
		}
	};
}