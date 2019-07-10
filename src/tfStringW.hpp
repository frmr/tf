#pragma once

#include "tfStringBase.hpp"

namespace tf
{
	class String;

	class StringW : public StringBase<wchar_t, StringW>
	{
	public:
		using StringBase<wchar_t, StringW>::StringBase;

		String ToUtf8() const;
	};
}