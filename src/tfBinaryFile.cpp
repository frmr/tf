#include "tfBinaryFile.hpp"
#include "tfUnreachableException.hpp"

#include <cstring>

tf::BinaryFile::BinaryFile(const String& filename) :
	m_file(filename, std::ios::binary),
	m_size(calculateSize())
{
	if (!isOpen())
	{
		throw std::runtime_error("BinaryFile::BinaryFile(): Couldn't open " + filename);
	}

	seek(0, SeekOrigin::Beg);
}

bool tf::BinaryFile::isOpen() const
{
	return m_file.is_open();
}

void tf::BinaryFile::seek(const int64_t& offset, const SeekOrigin origin)
{
	std::ios_base::seekdir dir;

	switch (origin)
	{
	case SeekOrigin::Beg: dir = std::ios::beg; break;
	case SeekOrigin::Cur: dir = std::ios::cur; break;
	case SeekOrigin::End: dir = std::ios::end; break;
	default:              throw UnreachableException("Invalid SeekOrigin");
	}

	m_file.seekg(offset, dir);
}

void tf::BinaryFile::read(const int64_t& bytes, tf::Vector<uint8_t>& buffer)
{
	buffer.resize(size_t(bytes));

	m_file.read(reinterpret_cast<char*>(buffer.data()), bytes);
}

void tf::BinaryFile::read(Vector<uint8_t>& buffer)
{
	read(getSize(), buffer);
}

tf::Vector<uint8_t> tf::BinaryFile::toBuffer()
{
	tf::Vector<uint8_t> buffer;

	read(buffer);

	return buffer;
}

tf::String tf::BinaryFile::toString()
{
	const tf::Vector<uint8_t> buffer = toBuffer();
	tf::String                string;

	string.resize(buffer.size(), 'r');
	std::memcpy(const_cast<char*>(string.data()), buffer.data(), string.size());

	return string;
}

int64_t tf::BinaryFile::getSize() const
{
	return m_size;
}

int64_t tf::BinaryFile::calculateSize()
{
	seek(0, SeekOrigin::End);

	return m_file.tellg();
}
