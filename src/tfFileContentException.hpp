#pragma once

#include <stdexcept>
#include "tfString.hpp"

namespace tf
{
	class FileContentException : public std::runtime_error
	{
	public:
		FileContentException(const String& what) :
			std::runtime_error("tf::FileContentException: " + what)
		{
		}
	};
}