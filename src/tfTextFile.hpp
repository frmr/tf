#pragma once

#include "tfString.hpp"
#include <vector>

namespace tf
{
	class TextFile
	{
	public:
		               TextFile(const String& filename);

		String         GetLine(const size_t index) const;
		Vector<String> GetLines() const;

		void           WriteLine(const String& line);
		void           WriteLines(const Vector<String>& lines);

		void           AppendLine(const String& line);
		void           AppendLines(const Vector<String>& lines);
		
		virtual void   Reload();

		String         ToString() const;

	private:
		void           WriteLinesToFile() const;

	protected:
		const String   m_filename;
		Vector<String> m_lines;
	};
}