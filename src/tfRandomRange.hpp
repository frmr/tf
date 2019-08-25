#pragma once

#include <cmath>
#include <random>
#include <ctime>

namespace tf
{
	template<typename T>
	class RandomRange
	{
	public:
		RandomRange(const T min, const T max, const unsigned int seed = 0) :
			m_engine(seed),
			m_distribution(double(min), double(max))
		{
		}

		T sample()
		{
			return (T) m_distribution(m_engine);
		}
	
	private:
		std::mt19937                           m_engine;
		std::uniform_real_distribution<double> m_distribution;
	};
}