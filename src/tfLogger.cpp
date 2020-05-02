#include "tfLogger.hpp"
#include <fstream>
#include <ctime>
#include <iomanip>
#include <filesystem>

tf::String   tf::Logger::m_filenamePrefix("default");
tf::String   tf::Logger::m_filenameSuffix(".log");
tf::String   tf::Logger::m_folder("");
tf::LogGroup tf::Logger::m_group(LogGroup::None);
std::mutex   tf::Logger::m_mutex;

void tf::Logger::log(const String& message)
{
	const String          isoDatetime = getTime();
	const String          year        = isoDatetime.substr(0, 4);
	const String          month       = isoDatetime.substr(5, 2);
	const String          day         = isoDatetime.substr(8, 2);
	std::filesystem::path path        = m_folder.c_str();

	if (m_group == LogGroup::Month)
	{
		path.append(year.c_str());
	}
	else if (m_group == LogGroup::Day)
	{
		path.append(year.c_str());
		path.append(month.c_str());
	}

	std::unique_lock<std::mutex> lock(m_mutex);

	if (path.empty() || std::filesystem::exists(path) || std::filesystem::create_directories(path))
	{
		path.append(m_filenamePrefix.c_str());

		if      (m_group == LogGroup::Year ) { path += "_" + year;                           }
		else if (m_group == LogGroup::Month) { path += "_" + year + "-" + month;             }
		else if (m_group == LogGroup::Day  ) { path += "_" + year + "-" + month + "-" + day; }

		path += m_filenameSuffix.c_str();

		std::ofstream logFile(path, std::ios::app);

		if (logFile.is_open())
		{
			logFile << isoDatetime + "  \t" + message << std::endl;
			logFile.close();
		}
	}
}

void tf::Logger::setFilenamePrefix(const String& prefix)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_filenamePrefix = prefix;
}

void tf::Logger::setFilenameSuffix(const String& suffix)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_filenameSuffix = suffix;
}

void tf::Logger::setFolder(const String& folder)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_folder = folder;
}

void tf::Logger::setGroup(const LogGroup group)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_group = group;
}

tf::String tf::Logger::getTime()
{
	// TODO: Replace all of this with std methods if/when nice ones become available

	const time_t       time = std::time(nullptr);
	std::tm            tm   = *std::localtime(&time);
	std::ostringstream oss;

	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

	return oss.str();
}
