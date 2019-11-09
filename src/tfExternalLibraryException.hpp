#pragma once

#include "tfString.hpp"

namespace tf
{
	class ExternalLibraryException : public std::runtime_error
	{
	public:
		ExternalLibraryException(const tf::String& what) :
			std::runtime_error("tf::ExternalLibraryException: " + what)
		{
		}
	};
}