#pragma once

#include "tfIniSection.hpp"
#include "tfTextFile.hpp"

namespace tf
{
	class IniFile : protected TextFile
	{
	public:
		                        IniFile(const String& filename);

		void                    Reload();
		void                    Save();
		String                  GetValue(const String& keyName) const;
		String                  GetValue(const String& sectionName, const String& keyName) const;
		void                    SetValue(const String& sectionName, const String& keyName, const String& keyValue);
		void                    SetValue(const String& keyName, const String& keyValue);
		Map<String, IniSection> GetSections() const;
		bool                    Contains(const String& keyName) const;
		bool                    Contains(const String& sectionName, const String& keyName) const;

	private:
		void                    Parse();

	private:
		Map<String, IniSection> m_sections;
	};
}