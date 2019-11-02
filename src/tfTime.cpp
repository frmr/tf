#include "tfTime.hpp"
#include <chrono>

tf::Time::Time() :
	m_timestamp(std::chrono::duration_cast<std::chrono::duration<int64_t>>(std::chrono::system_clock::now().time_since_epoch()).count())
{
}

tf::Time::Time(const int64_t& timestamp) :
	m_timestamp(timestamp)
{
}

int64_t tf::Time::getTimestamp() const
{
	return m_timestamp;
}
