#pragma once

#include <stdexcept>
#include "tfString.hpp"

namespace tf
{
	class UnreachableException : public std::runtime_error
	{
	public:
		UnreachableException(const String& what) :
			std::runtime_error("UnreachableException: " + what)
		{
		}
	};
}