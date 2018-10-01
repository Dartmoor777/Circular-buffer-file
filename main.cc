#include "cycle_buf.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

static size_t bufSize = 10;
static const char* logName = "logs.txt";
static char bufferTest[] = "9876543210zyxvtsrqponmlkihgfedcbaZYXVTSRQPONMLKIHGFEDCBAabcdefghiklmnopqrstvxyz0123456789ABCDEFGHIKLMNOPQRSTVXYZ";
static char bufferLog[sizeof(bufferTest)] = {};
static const size_t bufferTestSize = sizeof(bufferTest);
static char* bufferTestP = bufferTest;
static const char* bufferTestStart = bufferTest;
static char* bufferLogP = bufferLog;
static size_t offset = 0;

using namespace std;

bool testWrite(size_t howMuch, CycleBuf& cycleBuf)
{
	if ((bufferTestP - bufferTestStart) + howMuch > bufferTestSize){
		cout << "End of test log\n";
		return false;
	}
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	if (cycleBuf.getBufSize() + howMuch > bufSize) {
		offset += ((cycleBuf.getBufSize()+howMuch) - bufSize);
	}
	cycleBuf.writeBuf(bufferTestP, howMuch);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	cout << endl;
	bufferTestP += howMuch;


	if (memcmp(bufferTest + offset, bufferLogP, cycleBuf.getBufSize()) == 0) {
		return true;
	} else {
		printf("test buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferTest + offset);
		printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
		char tmpBuf[bufSize] = {};
		if (cycleBuf.dumpLogFile(tmpBuf, sizeof(tmpBuf)) < 0) printf("can't dumpLogFile file!\n");
		printf("file dump is\n%.*s\n\n", sizeof(tmpBuf), tmpBuf);
		return false;
	}
}

void checkWrite()
{


	CycleBuf cycleBuf(logName, bufSize);
	int writeValue = 0;
	size_t test = 1;

#define TEST_WRITE(vALUE)							\
	do{												\
		if(testWrite(vALUE, cycleBuf)) {			\
			cout << "test " << test << " success!" << endl;	\
		} else {									\
			cout << "test " << test << " fail!" << endl;	\
		}											\
		test++;										\
	}while(0)

	TEST_WRITE(2);
	TEST_WRITE(8);
	TEST_WRITE(7);
	TEST_WRITE(16);
	TEST_WRITE(4);
	TEST_WRITE(6);
	TEST_WRITE(2);
	TEST_WRITE(3);

}

void checkReadAndPersistence()
{
	CycleBuf cycleBuf(logName, bufSize);
	size_t test = 1;
	cout << endl;
	if(memcmp(bufferTest + offset, bufferLogP, cycleBuf.getBufSize()) == 0) {
		cout << "read test " << test << " success!" << endl;
	} else {
		cout << "read test " << test << "fail!" << endl;	
	}

}

int main()
{
	checkWrite();
	checkReadAndPersistence();

	cout << "CHECK SIZE CHANGE" << endl;
	bufSize = 15;
	bufferTestP = bufferTest;
	bufferLogP = bufferLog;
	offset = 0;

	checkWrite();
	checkReadAndPersistence();


	cout << "CHECK SIZE CHANGE TO LOWER" << endl;
	bufSize = 5;
	bufferTestP = bufferTest;
	bufferLogP = bufferLog;
	offset = 0;

	checkWrite();
	checkReadAndPersistence();

	remove(logName);
    return 0;
}
