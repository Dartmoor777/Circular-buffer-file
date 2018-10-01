#include <ctype.h>
#include <cstddef>
#include <string>

class CycleBuf {
public:
	CycleBuf(const char* logName, size_t maxSize);
	int readBuf(void* ptr, size_t size);
	int writeBuf(void* ptr, size_t size);
	int dumpLogFile(void *ptr, size_t size);
	size_t getBufSize() const {return _curSize;}
private:
	bool copy(const char* from, const char* name) const;
	int write(const void* ptr, size_t size) const;
	int read(void* ptr, size_t size) const;
	int seek(size_t pos) const;
	int open(const char* mode);
	int close();
	int openSwap(const char* mode);
	int closeSwap();
	bool copy(const char* from, const char* name);
	bool isOpen() const;
	size_t getHeaderSize() const;
	int writeHeader();
	int readHeader();
	size_t _maxSize;
	size_t _curSize;
	size_t _startPos;
	const char* _swapPrefix;
	std::string _logName;
	FILE* _log;
};
