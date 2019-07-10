#pragma once

#include <mutex>

namespace tf
{
	typedef std::unique_lock<std::mutex> Lock;
}