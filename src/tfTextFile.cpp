#include "tfTextFile.hpp"
#include "tfFileIoException.hpp"

#include <fstream>
#include <iostream>

tf::TextFile::TextFile(const String& filename) :
	m_filename(filename)
{
	reload();
}

tf::String tf::TextFile::getLine(const size_t index) const
{
	return index < m_lines.size() ? m_lines[index] : "";
}

std::vector<tf::String> tf::TextFile::getLines() const
{
	return m_lines;
}

void tf::TextFile::writeLine(const String& line)
{
	writeLines({line});
}

void tf::TextFile::writeLines(const std::vector<String>& lines)
{
	m_lines = lines;
	writeLinesToFile();
}

void tf::TextFile::appendLine(const String& line)
{
	appendLines({line});
}

void tf::TextFile::appendLines(const std::vector<String>& lines)
{
	m_lines.insert(m_lines.end(), lines.begin(), lines.end());
	writeLinesToFile();
}

void tf::TextFile::reload()
{
	std::ifstream file;
	String        line;

	m_lines.clear();
	file.open(m_filename);

	if (!file)
	{
		throw FileIoException(String("Failed to open file ({})", { m_filename }));
	}

	while(std::getline(file, line))
	{
		m_lines.push_back(line);
	}

	file.close();
}

tf::String tf::TextFile::toString() const
{
	String output;

	for (const String line : m_lines)
	{
		output += line;
	}

	return output;
}

void tf::TextFile::writeLinesToFile() const
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
