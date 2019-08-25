#include "tfString.hpp"
#include "tfStringW.hpp"

#include <locale>
#include <codecvt>
#include <algorithm>

tf::StringW tf::String::fromUtf8() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(*this);
}

void tf::String::toLower()
{
	std::transform(begin(), end(), begin(), ::tolower);
}
