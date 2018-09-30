#include <ctype.h>
#include <cstddef>
#include <string>

class CycleBuf {
public:
	CycleBuf(const char* logName, size_t maxSize);
	int readBuf(void* ptr, size_t size);
	int writeBuf(void* ptr, size_t size);

	// debug
	int dumpLogFile() const;
private:
	int write(const void* ptr, size_t size) const;
	int read(void* ptr, size_t size) const;
	int seek(size_t pos) const;
	int open(const char* mode);
	int close();
	bool isOpen() const;
	size_t getHeaderSize() const;
	int writeHeader();
	int readHeader();
	size_t _maxSize;
	size_t _curSize;
	size_t _startPos;
	std::string _logName;
	FILE* _log;
};
