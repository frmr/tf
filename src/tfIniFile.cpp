#include "tfIniFile.hpp"
#include "tfLogger.hpp"

tf::IniFile::IniFile(const String& filename) :
	TextFile(filename)
{
	Parse();
}

void tf::IniFile::Reload()
{
	TextFile::Reload();
	Parse();
}

void tf::IniFile::Save()
{
	tf::Vector<String> lines;

	if (m_sections.Contains(""))
	{
		const auto sectionLines = m_sections[""].ToLines();
		lines.insert(lines.end(), sectionLines.begin(), sectionLines.end());
	}

	for (const auto& sectionPair : m_sections)
	{
		if (sectionPair.first != "")
		{
			const auto sectionLines = sectionPair.second.ToLines();
			lines.insert(lines.end(), sectionLines.begin(), sectionLines.end());
		}
	}

	WriteLines(lines);
}

tf::String tf::IniFile::GetValue(const String& keyName) const
{
	return GetValue("", keyName);
}

tf::String tf::IniFile::GetValue(const String& sectionName, const String& keyName) const
{
	return m_sections.at(sectionName).GetValue(keyName);
}

void tf::IniFile::SetValue(const String& sectionName, const String& keyName, const String& keyValue)
{
	if (!m_sections.Contains(sectionName))
	{
		m_sections[sectionName] = IniSection(sectionName);
	}

	m_sections[sectionName].SetValue(keyName, keyValue);

	Save();
}

void tf::IniFile::SetValue(const String& keyName, const String& keyValue)
{
	SetValue("", keyName, keyValue);
}

tf::Map<tf::String, tf::IniSection> tf::IniFile::GetSections() const
{
	return m_sections;
}

bool tf::IniFile::Contains(const String& keyName) const
{
	return Contains("", keyName);
}

bool tf::IniFile::Contains(const String& sectionName, const String& keyName) const
{
	if (m_sections.Contains(sectionName))
	{
		return m_sections.at(sectionName).Contains(keyName);
	}
	else
	{
		return false;
	}
}

void tf::IniFile::Parse()
{
	String activeSectionName = "";
	size_t lineNumber        = 1;

	for (auto line : m_lines)
	{
		line.Strip();

		if (line.StartsWith("[") && line.EndsWith("]"))
		{
			activeSectionName = line.Middle(1, 1);

			if (!m_sections.Contains(activeSectionName))
			{
				m_sections[activeSectionName] = IniSection(activeSectionName);
			}
		}
		else if (!line.empty() && !line.StartsWith(";"))
		{
			auto parts = line.Split("=");

			if (parts.size() == 2)
			{
				parts.front().Strip();
				parts.back().Strip();

				m_sections[activeSectionName].SetValue(parts.front(), parts.back());
			}
			else
			{
				Logger::Log(String("Invalid INI syntax in file ({}) on line {}", {m_filename, std::to_string(lineNumber)}));
			}
		}

		++lineNumber;
	}
}
