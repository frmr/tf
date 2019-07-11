#include "tfTimer.hpp"

void tf::Timer::Reset()
{
	 m_start = std::chrono::high_resolution_clock::now();
}

double tf::Timer::GetMilliseconds()
{
	return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - m_start).count();
}