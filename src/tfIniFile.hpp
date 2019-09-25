#pragma once

#include "tfIniSection.hpp"
#include "tfTextFile.hpp"

namespace tf
{
	class IniFile : protected TextFile
	{
	public:
		                        IniFile(const String& filename);

		void                    reload() override;
		void                    save();
		String                  getValue(const String& keyName) const;
		String                  getValue(const String& sectionName, const String& keyName) const;
		void                    setValue(const String& sectionName, const String& keyName, const String& keyValue);
		void                    setValue(const String& keyName, const String& keyValue);
		Map<String, IniSection> getSections() const;
		bool                    contains(const String& keyName) const;
		bool                    contains(const String& sectionName, const String& keyName) const;

	private:
		void                    parse();

	private:
		Map<String, IniSection> m_sections;
	};
}