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

		String              GetName() const;
		Map<String, String> GetKeys() const;
		String              GetValue(const String& name) const;
		void                SetValue(const String& name, const String& value);
		std::vector<String> ToLines() const;
		bool                Contains(const String& name) const;

	private:
		String              m_name;
		Map<String, String> m_keys;
	};
}