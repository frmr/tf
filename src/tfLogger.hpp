#pragma once

#include "tfString.hpp"
#include <mutex>

namespace tf
{
	class Logger
	{
	public:
		static void Log(const String& message);
		static void SetFilename(const String& filename);

	private:
		static String GetTime();

	private:
		static String     m_filename;
		static std::mutex m_mutex;
	};
}