#include "tfString.hpp"
#include "tfStringW.hpp"

#include <locale>
#include <codecvt>
#include <algorithm>

tf::StringW tf::String::FromUtf8() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(*this);
}

void tf::String::ToLower()
{
	std::transform(begin(), end(), begin(), ::tolower);
}
