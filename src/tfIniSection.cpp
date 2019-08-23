#include "tfIniSection.hpp"

tf::IniSection::IniSection() :
	m_name("")
{
}

tf::IniSection::IniSection(const String& name) :
	m_name(name)
{
}

tf::String tf::IniSection::GetName() const
{
	return m_name;
}

tf::Map<tf::String, tf::String> tf::IniSection::GetKeys() const
{
	return m_keys;
}

tf::String tf::IniSection::GetValue(const String& name) const
{
	return m_keys.at(name);
}

void tf::IniSection::SetValue(const String& name, const String& value)
{
	m_keys[name] = value;
}

std::vector<tf::String> tf::IniSection::ToLines() const
{
	std::vector<String> lines;

	if (!m_name.empty())
	{
		lines.push_back("[" + m_name + "]");
	}

	for (const auto& key : m_keys)
	{
		lines.push_back(key.first + "=" + key.second);
	}

	lines.push_back("");

	return lines;
}

bool tf::IniSection::Contains(const String& name) const
{
	return m_keys.Contains(name);
}
