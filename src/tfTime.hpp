#pragma once

#include <cstdint>

namespace tf
{
	class Time
	{
	public:
		        Time();
		        Time(const int64_t& timestamp);

		int64_t getTimestamp() const;

	private:
		int64_t m_timestamp;
	};
}