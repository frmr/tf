#pragma once

#include <chrono>

namespace tf
{
	class Timer
	{
	public:
		                                                            Timer();

		void                                                        reset();
		double                                                      getMilliseconds() const;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};
}