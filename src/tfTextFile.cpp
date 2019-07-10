#include "tfTextFile.hpp"
#include "tfFileIoException.hpp"

#include <fstream>
#include <iostream>

tf::TextFile::TextFile(const String& filename) :
	m_filename(filename)
{
	Reload();
}

tf::String tf::TextFile::GetLine(const size_t index) const
{
	return index < m_lines.size() ? m_lines[index] : "";
}

tf::Vector<tf::String> tf::TextFile::GetLines() const
{
	return m_lines;
}

void tf::TextFile::WriteLine(const String& line)
{
	WriteLines({line});
}

void tf::TextFile::WriteLines(const Vector<String>& lines)
{
	m_lines = lines;
	WriteLinesToFile();
}

void tf::TextFile::AppendLine(const String& line)
{
	AppendLines({line});
}

void tf::TextFile::AppendLines(const Vector<String>& lines)
{
	m_lines.insert(m_lines.end(), lines.begin(), lines.end());
	WriteLinesToFile();
}

void tf::TextFile::Reload()
{
	std::ifstream file;
	String        line;

	m_lines.clear();
	file.open(m_filename);

	if (!file)
	{
		throw FileIoException(String("Failed to open file ({})", {m_filename}));
	}

	while(std::getline(file, line))
	{
		m_lines.push_back(line);
	}

	file.close();
}

tf::String tf::TextFile::ToString() const
{
	String output;

	for (const String line : m_lines)
	{
		output += line;
	}

	return output;
}

void tf::TextFile::WriteLinesToFile() const
{
	std::ofstream file(m_filename, std::ios::binary);

	if (!file)
	{
		throw FileIoException(String("Failed to open file ({})", {m_filename}));
	}

	for (auto lineIt = m_lines.cbegin(); lineIt != m_lines.cend(); ++lineIt)
	{
		file << *lineIt;

		if (lineIt != m_lines.cend() - 1)
		{
			file << std::endl;
		}
	}

	file.close();
}
