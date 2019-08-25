#pragma once

#include "tfString.hpp"
#include <mutex>

namespace tf
{
	class Logger
	{
	public:
		static void       log(const String& message);
		static void       setFilename(const String& filename);

	private:
		static String     getTime();

	private:
		static String     m_filename;
		static std::mutex m_mutex;
	};
}