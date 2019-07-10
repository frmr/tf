#pragma once

#include "tfStringBase.hpp"

namespace tf
{
	class StringW;

	class String : public StringBase<char, String>
	{
	public:
		using StringBase<char, String>::StringBase;

		StringW FromUtf8() const;
		void    ToLower();
	};
}

namespace std
{
	template<> struct hash<tf::String>
	{
		size_t operator()(const tf::String& s) const noexcept
		{
			return std::hash<std::string>{}(s);
		}
	};
}