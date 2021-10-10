#include "tfIniFile.hpp"
#include "tfLogger.hpp"

tf::IniFile::IniFile(const String& filename) :
	TextFile(filename)
{
	parse();
}

void tf::IniFile::reload()
{
	TextFile::reload();
	parse();
}

void tf::IniFile::save()
{
	std::vector<String> lines;

	if (m_sections.contains(""))
	{
		const auto sectionLines = m_sections[""].toLines();
		lines.insert(lines.end(), sectionLines.begin(), sectionLines.end());
	}

	for (const auto& sectionPair : m_sections)
	{
		if (sectionPair.first != "")
		{
			const auto sectionLines = sectionPair.second.toLines();
			lines.insert(lines.end(), sectionLines.begin(), sectionLines.end());
		}
	}

	writeLines(lines);
}

tf::String tf::IniFile::getValue(const String& keyName) const
{
	return getValue("", keyName);
}

tf::String tf::IniFile::getValue(const String& sectionName, const String& keyName) const
{
	return m_sections.at(sectionName).getValue(keyName);
}

void tf::IniFile::setValue(const String& sectionName, const String& keyName, const String& keyValue)
{
	if (!m_sections.contains(sectionName))
	{
		m_sections[sectionName] = IniSection(sectionName);
	}

	m_sections[sectionName].setValue(keyName, keyValue);

	save();
}

void tf::IniFile::setValue(const String& keyName, const String& keyValue)
{
	setValue("", keyName, keyValue);
}

tf::Map<tf::String, tf::IniSection> tf::IniFile::getSections() const
{
	return m_sections;
}

bool tf::IniFile::contains(const String& keyName) const
{
	return contains("", keyName);
}

bool tf::IniFile::contains(const String& sectionName, const String& keyName) const
{
	if (m_sections.contains(sectionName))
	{
		return m_sections.at(sectionName).contains(keyName);
	}
	else
	{
		return false;
	}
}

void tf::IniFile::parse()
{
	String activeSectionName = "";
	size_t lineNumber        = 1;

	for (auto line : m_lines)
	{
		line.strip();

		if (line.startsWith("[") && line.endsWith("]"))
		{
			activeSectionName = line.middle(1, 1);

			if (!m_sections.contains(activeSectionName))
			{
				m_sections[activeSectionName] = IniSection(activeSectionName);
			}
		}
		else if (!line.empty() && !line.startsWith(";"))
		{
			auto parts = line.split("=");

			if (parts.size() == 2)
			{
				parts.front().strip();
				parts.back().strip();

				m_sections[activeSectionName].setValue(parts.front(), parts.back());
			}
			else
			{
				Logger::log(String("Invalid INI syntax in file ({}) on line {}", {m_filename, std::to_string(lineNumber)}));
			}
		}

		++lineNumber;
	}
}
