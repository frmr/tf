#include "tfBinaryFile.hpp"

tf::BinaryFile::BinaryFile(const String& filename) :
	m_file(filename, std::ios::binary),
	m_size(CalculateSize())
{
	if (!IsOpen())
	{
		throw std::runtime_error("BinaryFile::BinaryFile(): Couldn't open " + filename);
	}

	Seek(0, SeekOrigin::BEG);
}

bool tf::BinaryFile::IsOpen() const
{
	return m_file.is_open();
}

void tf::BinaryFile::Seek(const int64_t& offset, const SeekOrigin origin)
{
	std::ios_base::seekdir dir;

	switch (origin)
	{
	case SeekOrigin::BEG: dir = std::ios::beg; break;
	case SeekOrigin::CUR: dir = std::ios::cur; break;
	case SeekOrigin::END: dir = std::ios::end; break;
	}

	m_file.seekg(offset, dir);
}

void tf::BinaryFile::Read(const int64_t& bytes, tf::Vector<uint8_t>& buffer)
{
	buffer.resize(bytes);

	m_file.read(reinterpret_cast<char*>(buffer.data()), bytes);
}

void tf::BinaryFile::Read(Vector<uint8_t>& buffer)
{
	Read(GetSize(), buffer);
}

tf::Vector<uint8_t> tf::BinaryFile::ToBuffer()
{
	tf::Vector<uint8_t> buffer;

	Read(buffer);

	return buffer;
}

int64_t tf::BinaryFile::GetSize() const
{
	return m_size;
}

int64_t tf::BinaryFile::CalculateSize()
{
	Seek(0, SeekOrigin::END);

	return m_file.tellg();
}
