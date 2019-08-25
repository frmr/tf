#pragma once

#include "tfString.hpp"
#include <vector>

namespace tf
{
	class TextFile
	{
	public:
		               TextFile(const String& filename);

		String         getLine(const size_t index) const;
		Vector<String> getLines() const;

		void           writeLine(const String& line);
		void           writeLines(const Vector<String>& lines);

		void           appendLine(const String& line);
		void           appendLines(const Vector<String>& lines);
		
		virtual void   reload();

		String         toString() const;

	private:
		void           writeLinesToFile() const;

	protected:
		const String   m_filename;
		Vector<String> m_lines;
	};
}