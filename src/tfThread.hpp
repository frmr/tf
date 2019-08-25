#pragma once

#include <future>
#include <functional>
#include "tfWait.hpp"

namespace tf
{
	template<typename T>
	class Thread
	{
	public:
		typedef void (T::*MethodPtr) (const bool&);

		Thread(T* caller, MethodPtr method) :
			m_caller(caller),
			m_method(method),
			m_exit(false)
		{
		}

		void start()
		{
			if (!IsRunning())
			{
				m_exit = false;
				m_task = std::async(std::launch::async, std::bind(m_method, m_caller, std::cref(m_exit)));
			}
		}

		void stop(const Wait wait)
		{
			if (IsRunning())
			{
				m_exit = true;

				if (wait == Wait::Wait)
				{
					m_task.wait();
				}
			}
		}

		bool isRunning() const
		{
			return m_task.valid() && (m_task.wait_for(std::chrono::seconds(0)) == std::future_status::timeout);
		}

	private:
		T*                m_caller;
		MethodPtr         m_method;
		std::future<void> m_task;
		bool              m_exit;
	};
}