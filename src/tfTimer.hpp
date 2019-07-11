#pragma once

#include <chrono>

namespace tf
{
	class Timer
	{
	public:
		void                                                        Reset();
		double                                                      GetMilliseconds();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};
}