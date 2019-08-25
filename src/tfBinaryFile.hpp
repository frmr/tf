#pragma once

#include "tfString.hpp"
#include "tfSeekOrigin.hpp"
#include <cstdint>
#include <fstream>

namespace tf
{
	class BinaryFile
	{
	public:
		                BinaryFile(const String& filename);

		bool            isOpen() const;
		void            seek(const int64_t& offset, const SeekOrigin origin);
		void            read(const int64_t& bytes, Vector<uint8_t>& buffer);
		void            read(Vector<uint8_t>& buffer);
		Vector<uint8_t> toBuffer();
		int64_t         getSize() const;

	private:
		int64_t         calculateSize();

	private:
		std::ifstream   m_file;
		const int64_t   m_size;
	};
}