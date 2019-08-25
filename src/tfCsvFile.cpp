#include "tfCsvFile.hpp"

tf::CsvFile::CsvFile(const String& filename, const Vector<String>& columns) :
	TextFile(filename),
	m_columns(columns)
{
	parse();
}

bool tf::CsvFile::parse()
{
	bool success = true;

	m_entries.reserve(m_lines.size());

	for (const auto& line : m_lines)
	{
		try
		{
			m_entries.push_back(parseLine(line));
		}
		catch (const std::out_of_range&)
		{
			Logger::log(tf::String("Too few elements on line in CsvFile ({}) with content:", { m_filename }));
			Logger::log(line);

			success = false;
		}
		catch (const FileContentException&)
		{
			Logger::log(String("Failed to parse line in CsvFile ({}) with content:", { m_filename }));
			Logger::log(line);

			success = false;
		}
	}

	return success;
}

const tf::Vector<tf::CsvLine>& tf::CsvFile::getEntries() const
{
	return m_entries;
}

void tf::CsvFile::write(const Vector<CsvLine>& entries)
{
	Vector<String> lines;

	for (const CsvLine& entry : entries)
	{
		lines.push_back("");

		for (auto element = entry.begin(); element != entry.end(); ++element)
		{
			lines.back().append(element->second);

			if (element != std::prev(entry.end()))
			{
				lines.back().append(", ");
			}
		}
	}

	writeLines(lines);
}

tf::CsvLine tf::CsvFile::parseLine(const String & line) const
{
	CsvLine  entry;
	String   element;

	bool     inQuotes = false;
	bool     escaping = false;
	size_t   columnIndex = 0;

	for (const auto& character : line)
	{
		if (character == '"')
		{
			if (escaping)
			{
				element.push_back('"');
				escaping = false;
			}
			else if (inQuotes)
			{
				inQuotes = false;
			}
			else
			{
				String stripped = element;
				stripped.strip();

				if (stripped.empty())
				{
					inQuotes = true;
				}
				else
				{
					throw FileContentException(String("Quotes opened in the middle of an element in CsvFile ({})", { m_filename }));
				}
			}
		}
		else if (character == ',')
		{
			if (escaping)
			{
				throw FileContentException(String("Cannot escape character (,) in CsvFile ({})", { m_filename }));
			}
			else if (inQuotes)
			{
				element.push_back(',');
			}
			else
			{
				if (columnIndex >= m_columns.size())
				{
					throw FileContentException(String("Too many columns in CsvFile ({})", { m_filename }));
				}

				entry[m_columns[columnIndex++]] = element;
				element.clear();
			}
		}
		else if (character == '\\')
		{
			if (escaping)
			{
				element.push_back('\\');
				escaping = false;
			}
			else
			{
				escaping = true;
			}
		}
		else
		{
			if (escaping)
			{
				std::stringstream stream;

				stream << character;

				throw FileContentException(String("Cannot escape character ({}) in CsvFile ({})", { stream.str(), m_filename }));
			}
			else
			{
				element.push_back(character);
			}
		}
	}

	if (escaping)
	{
		throw FileContentException(String("Line must not end with \\ in CsvFile ({})", { m_filename }));
	}
	else if (inQuotes)
	{
		throw FileContentException(String("No closing quote found in CsvFile ({})", { m_filename }));
	}
	else if (!element.empty() || line.back() == ',')
	{
		if (columnIndex >= m_columns.size())
		{
			throw FileContentException(String("Too many columns in CsvFile ({})", { m_filename }));
		}

		element.strip();
		entry[m_columns[columnIndex++]] = element;
	}

	if (entry.size() != m_columns.size())
	{
		throw tf::FileContentException(tf::String("Incorrect number of entries on word file line ({}). Expected {}, got {}.", { m_filename, std::to_string(m_columns.size()), std::to_string(line.size()) }));
	}

	return entry;
}
