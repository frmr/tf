#pragma once

#include <vector>

namespace tf
{
	template<typename T>
	class Vector : public std::vector<T>
	{
	public:
		using std::vector<T>::vector;

		void append(const Vector<T>& other)
		{
			std::vector<T>::insert(this->end(), other.begin(), other.end());
		}
	};
}