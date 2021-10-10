#pragma once

#include "tfTextFile.hpp"
#include "tfCsvLine.hpp"
#include "tfFileContentException.hpp"
#include "tfLogger.hpp"

namespace tf
{
	class CsvFile : protected TextFile
	{
	public:
		                            CsvFile(const String& filename, const std::vector<String>& columns);

		bool                        parse();
		const std::vector<CsvLine>& getEntries() const;
		void                        write(const std::vector<CsvLine>& entries);
		
	protected:

		CsvLine                     parseLine(const String& line) const;

	private:
		const std::vector<String>   m_columns;
		std::vector<CsvLine>        m_entries;
	};
}