#pragma once

#include <cstdint>

namespace tf
{
	class Time
	{
	public:
		         Time();
		         Time(const uint64_t& timestamp);

		uint64_t getTimestamp() const;

	private:
		uint64_t m_timestamp;
	};
}