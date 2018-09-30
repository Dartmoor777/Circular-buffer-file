#include "cycle_buf.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

static size_t bufSize = 4096;
static const char* logName = "logs.txt";

using namespace std;

int main()
{
	// init
	char bufferTest[32768] = {};
	char bufferLog[32768] = {};
	char* bufferTestP = bufferTest;
	char* bufferLogP = bufferLog;

	CycleBuf cycleBuf(logName, bufSize);
	std::ifstream stream("test.txt");
	stream.read(bufferTestP, bufSize * 2);

	// test 1
	int compareSize = 3072;
	cycleBuf.writeBuf(bufferTestP, compareSize);
	cycleBuf.readBuf(bufferLogP, compareSize);
	if (memcmp(bufferTestP, bufferLogP, compareSize) == 0) {
		cout << "first check is OK!" << endl;
	}

	// test 2

	int written = 0;
	if ((written = cycleBuf.writeBuf(bufferTestP, 2048)) <= 0) cout << "Error is here" << __LINE__ << endl;
	cout << "Written " << written << endl;
	if ((written = cycleBuf.readBuf(bufferLogP, 4096)) <= 0) cout << "Error is here" << __LINE__ << endl;
	cout << "Written " << written << endl;

	bufferTestP += 1024;
	if (memcmp(bufferTestP, bufferLogP, compareSize) == 0) {
		cout << "second check is OK!" << endl;
	} else {
		cout << "test buf is " << endl << bufferTestP << "log buf is" << endl << bufferLogP << endl;
		cout << "file content is" << endl << cycleBuf.dumpLogFile();
	}

	remove(logName);
    return 0;
}
