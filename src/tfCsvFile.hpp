#pragma once

#include "tfTextFile.hpp"
#include "tfCsvLine.hpp"
#include "tfFileContentException.hpp"
#include "tfVector.hpp"
#include "tfLogger.hpp"

namespace tf
{
	class CsvFile : protected TextFile
	{
	public:
		                       CsvFile(const String& filename, const Vector<String>& columns);

		bool                   parse();
		const Vector<CsvLine>& getEntries() const;
		void                   write(const Vector<CsvLine>& entries);
		
	protected:

		CsvLine                parseLine(const String& line) const;

	private:
		const Vector<String>   m_columns;
		Vector<CsvLine>        m_entries;
	};
}