#include "tfString.hpp"
#include "tfStringW.hpp"

#include <locale>
#include <codecvt>

tf::String tf::StringW::ToUtf8() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(*this);
}
