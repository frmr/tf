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

		bool            IsOpen() const;
		void            Seek(const int64_t& offset, const SeekOrigin origin);
		void            Read(const int64_t& bytes, Vector<uint8_t>& buffer);
		void            Read(Vector<uint8_t>& buffer);
		Vector<uint8_t> ToBuffer();
		int64_t         GetSize() const;

	private:
		int64_t         CalculateSize();

	private:
		std::ifstream   m_file;
		const int64_t   m_size;
	};
}