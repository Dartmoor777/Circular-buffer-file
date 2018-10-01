#include "cycle_buf.h"
#include <cstdio>
#include <stdint.h>

CycleBuf::CycleBuf(const char* logName, size_t maxSize) :
	_maxSize(maxSize),
	_curSize(0),
	_startPos(0),
	_logName(logName),
	_log(NULL)
{
	if (open("rb") == 0) {
		readHeader();

		// header size changed, reinit
		if (_maxSize != maxSize) {
			open("w"); // rewrite log file
			_maxSize = maxSize;
			_startPos = 0;
			_curSize = 0;
			writeHeader();
		}

	} else {
		open("w");
		writeHeader();
	}
	close();
}

int CycleBuf::write(const void *ptr, size_t size) const
{
	if (!isOpen()) return -1;
	return fwrite(ptr, sizeof(uint8_t), size, _log);
}

int CycleBuf::read(void *ptr, size_t size) const
{
	if (!isOpen()) return -1;
	return fread(ptr, sizeof(uint8_t), size, _log);
}

int CycleBuf::seek(size_t pos) const
{
	if (!isOpen()) return -1;
	return fseek(_log, pos + getHeaderSize(), SEEK_SET);
}

int CycleBuf::open(const char* mode)
{
	if (!isOpen()) {
		_log = fopen(_logName.c_str(), mode);
	} else {
		_log = freopen(_logName.c_str(), mode, _log);
	}
	return isOpen() ? 0 : -1;
}

int CycleBuf::close()
{
	if (isOpen()) {
		int stat = fclose(_log);
		_log = NULL;
		return stat;
	}
	return 0;
}

bool CycleBuf::isOpen() const
{
	return _log != NULL;
}

size_t CycleBuf::getHeaderSize() const
{
	return
		sizeof(_maxSize) +
		sizeof(_curSize) +
		sizeof(_startPos);
}

int CycleBuf::writeBuf(void *ptr, size_t size)
{
	if (size == 0) return 0;

	size_t writePos = ((_startPos + _curSize) % _maxSize);

	if (ptr == NULL ||
		open("rb+") < 0 ||
		seek(writePos) < 0) return -1;

	// no need to write data bigger than buffer, write only its last part
	if (size > _maxSize) {
		ptr = (uint8_t*)ptr + (size - _maxSize);
		size = _maxSize;
	}

	size_t leftSize = _maxSize - writePos;
	if (leftSize > _maxSize) return -1; // check overflow

	int written = write(ptr, (leftSize < size) ? leftSize : size);
	if (written < 0) return -1;

	if (leftSize < size) {
		seek(0);
		written += write((uint8_t*)ptr + written, size - written);
	}

	_curSize += size;
	if (_curSize > _maxSize) {
		_startPos += (_curSize % _maxSize);
		_startPos = (_startPos % _maxSize);
		_curSize = _maxSize;
	}

	if (close() == EOF) return -1;

	writeHeader();

	return (size_t)written == size ? written : -1;
}

int CycleBuf::readBuf(void *ptr, size_t size)
{
	if (size == 0) return 0;

	if (ptr == NULL ||
		open("rb") < 0 ||
		seek(_startPos) < 0) return -1;

	// will be read exactly how much we have
	if (size > _curSize) size = _curSize;

	size_t leftSize = _maxSize - _startPos;
	if (leftSize > _maxSize) return -1; // check overflow

	int wasRead = read(ptr, (leftSize < size) ? leftSize : size);
	if (wasRead < 0) return -1;

	if (leftSize < size) {
		seek(0);
		ptr = ((uint8_t*)ptr) + wasRead;
		wasRead += read(ptr, size - wasRead);
	}

	if (close() == EOF) return -1;
	return (size_t)wasRead == size ? wasRead : -1;
}

int CycleBuf::writeHeader()
{
	if (open("rb+") < 0) return -1;
	rewind(_log);

	int written = 0;
	written += write(&_maxSize, sizeof(_maxSize));
	written += write(&_curSize, sizeof(_curSize));
	written += write(&_startPos, sizeof(_startPos));

	if (close() == EOF) return -1;
	return (size_t)written == getHeaderSize() ? written : -1;
}

int CycleBuf::readHeader()
{
	if (open("rb") < 0) return -1;
	rewind(_log);

	int wasRead = 0;
	wasRead += read((void*)&_maxSize, sizeof(_maxSize));
	wasRead += read((void*)&_curSize, sizeof(_curSize));
	wasRead += read((void*)&_startPos, sizeof(_startPos));

	if (close() == EOF) return -1;
	return (size_t)wasRead == getHeaderSize() ? wasRead : -1;
}

int CycleBuf::dumpLogFile(void *ptr, size_t size)
{
	if (size == 0) return 0;

	if (ptr == NULL ||
		open("rb") < 0 ||
		seek(0) < 0) return -1;

	// will be read exactly how much we have
	if (size > _curSize) size = _curSize;

	int wasRead = read(ptr, size);
	if (wasRead < 0) return -1;

	if (close() == EOF) return -1;
	return (size_t)wasRead == size ? wasRead : -1;
}
