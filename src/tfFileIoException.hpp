#pragma once

#include <stdexcept>
#include "tfString.hpp"

namespace tf
{
	class FileIoException : public std::runtime_error
	{
	public:
		FileIoException(const String& what) :
			std::runtime_error("FileIoException: " + what)
		{
		}
	};
}