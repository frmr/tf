#include "tfLogger.hpp"
#include <fstream>
#include <ctime>
#include <iomanip>

tf::String tf::Logger::m_filename("default.log");
std::mutex tf::Logger::m_mutex;

void tf::Logger::Log(const String& message)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::ofstream               logFile(m_filename, std::ios::app);

	logFile << GetTime() + "  \t" + message << std::endl;
	logFile.close();
}

void tf::Logger::SetFilename(const String& filename)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_filename = filename;
}

tf::String tf::Logger::GetTime()
{
	const time_t       time = std::time(nullptr);
	std::tm            tm   = *std::localtime(&time);
	std::ostringstream oss;

	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

	return oss.str();
}
