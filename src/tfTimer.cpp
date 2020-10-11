#include "tfTimer.hpp"

tf::Timer::Timer()
{
	reset();
}

void tf::Timer::reset()
{
	 m_start = std::chrono::high_resolution_clock::now();
}

double tf::Timer::getMilliseconds() const
{
	return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_start).count();
}
