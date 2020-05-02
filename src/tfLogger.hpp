#pragma once

#include "tfString.hpp"
#include "tfLogGroup.hpp"
#include <mutex>

namespace tf
{
	class Logger
	{
	public:
		static void       log(const String& message);
		static void       setFilenamePrefix(const String& prefix);
		static void       setFilenameSuffix(const String& suffix);
		static void       setFolder(const String& folder);
		static void       setGroup(const LogGroup group);

	private:
		static String     getTime();

	private:
		static String     m_filenamePrefix;
		static String     m_filenameSuffix;
		static String     m_folder;
		static LogGroup   m_group;
		static std::mutex m_mutex;
	};
}