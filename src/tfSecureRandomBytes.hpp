#pragma once

#ifdef _WIN32
# include <windows.h>
# define RtlGenRandom SystemFunction036
# if defined(__cplusplus)
extern "C"
# endif
BOOLEAN NTAPI RtlGenRandom(PVOID RandomBuffer, ULONG RandomBufferLength);
# pragma comment(lib, "advapi32.lib")
#else
#endif

#include "tfExternalLibraryException.hpp"
#include <type_traits>
#include <limits>
#include <cstdint>
#include <cassert>

namespace tf
{
	class SecureRandomBytes
	{
	public:
		static void get(void* buffer, size_t size)
		{
			#ifdef _WIN32

			if (!RtlGenRandom(buffer, ULONG(size)))
			{
				throw ExternalLibraryException("RtlGenRandom failed");	
			}

			#else

			assert(false);
			// TODO: implement for Linux

			#endif
		}

		template<typename T>
		static T get()
		{
			T value;

			get(&value, sizeof(value));

			return value;
		}
	};
}