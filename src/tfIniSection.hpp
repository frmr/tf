#pragma once

#include "tfMap.hpp"
#include "tfString.hpp"

#include <vector>

namespace tf
{
	class IniSection
	{
	public:
		                    IniSection();
		                    IniSection(const String& name);

		String              getName() const;
		Map<String, String> getKeys() const;
		String              getValue(const String& name) const;
		void                setValue(const String& name, const String& value);
		std::vector<String> toLines() const;
		bool                contains(const String& name) const;

	private:
		String              m_name;
		Map<String, String> m_keys;
	};
}