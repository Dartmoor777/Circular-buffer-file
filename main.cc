#include "cycle_buf.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

static size_t bufSize = 10;
static const char* logName = "logs.txt";

using namespace std;

int main()
{
	char bufferTest[] = "ABCDEFGHIKLMNOPQRSTVXYZabcdefghiklmnopqrstvxyz0123456789";
	char bufferLog[sizeof(bufferTest)] = {};
	size_t bufferTestSize = sizeof(bufferTest);
	char* bufferTestP = bufferTest;
	char* bufferLogP = bufferLog;
	size_t offset = 0;

	CycleBuf cycleBuf(logName, bufSize);
	// std::ifstream stream("test.txt");
	// stream.read(bufferTestP, bufSize * 2);
	int writeValue = 0;

	writeValue = 10;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;

	writeValue = 7;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;

	writeValue = 4;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;

	writeValue = 5;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;


	writeValue = 3;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;

	writeValue = 6;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;

	writeValue = 8;
	memset(bufferLogP, 0, sizeof(bufferTestSize));
	cycleBuf.writeBuf(bufferTestP, writeValue);
	cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	printf("test buf is\n%.*s\n\n", writeValue, bufferTestP);
	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	cycleBuf.dumpLogFile();
	cout << endl;
	bufferTestP += writeValue;
	// writeValue = 7;
	// // // test 1
	// offset += (cycleBuf.getBufSize() + writeValue) > bufSize ?
	// 	(cycleBuf.getBufSize() + writeValue) % bufSize : 0;
	// cycleBuf.writeBuf(bufferTestP, writeValue);
	// cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	// if (memcmp(bufferTest + offset, bufferLogP, cycleBuf.getBufSize()) == 0) {
	// 	cout << "first check is OK!" << endl;
	// }
	// bufferTestP += writeValue;

	// // test 2
	// writeValue = 4;
	// offset += (cycleBuf.getBufSize() + writeValue) > bufSize ?
	// 	(cycleBuf.getBufSize() + writeValue) % bufSize : 0;
	// cycleBuf.writeBuf(bufferTestP, writeValue);
	// cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	// if (memcmp(bufferTest + offset, bufferLogP, cycleBuf.getBufSize()) == 0) {
	// 	cout << "second check is OK!" << endl;
	// }
	// bufferTestP += writeValue;
	

	// // test 3
	// writeValue = 4;
	// offset += (cycleBuf.getBufSize() + writeValue) > bufSize ?
	// 	(cycleBuf.getBufSize() + writeValue) % bufSize : 0;
	// cycleBuf.writeBuf(bufferTestP, writeValue);
	// cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	// if (memcmp(bufferTest + offset, bufferLogP, cycleBuf.getBufSize()) == 0) {
	// 	cout << "third check is OK!" << endl;
	// } else {
	// 	printf("test buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferTest + offset);
	// 	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	// }
	// bufferTestP += writeValue;


	// // test 3
	// writeValue = 4;
	// offset += (cycleBuf.getBufSize() + writeValue) > bufSize ?
	// 	(cycleBuf.getBufSize() + writeValue) % bufSize : 0;
	// cycleBuf.writeBuf(bufferTestP, writeValue);
	// cycleBuf.readBuf(bufferLogP, cycleBuf.getBufSize());
	// if (memcmp(bufferTest + offset, bufferLogP, cycleBuf.getBufSize()) == 0) {
	// 	cout << "third check is OK!" << endl;
	// } else {
	// 	printf("test buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferTest + offset);
	// 	printf("log buf is\n%.*s\n\n", cycleBuf.getBufSize(), bufferLogP);
	// }
	// bufferTestP += writeValue;
	// // test 2
	// cycleBuf.writeBuf(bufferTestP, 5);
	// cycleBuf.readBuf(bufferLogP, 10);
	// if (memcmp(bufferTest + 2, bufferLogP, 10) == 0) {
	// 	cout << "second check is OK!" << endl;
	// } else {
	// 		printf("test buf is\n%.*s\n\n", 10, bufferTest + 2);
	// 		printf("log buf is\n%.*s\n\n", 10, bufferLogP);
	// }

	// bufferTestP += 5;
	// int compareSize = 3072;
	// cycleBuf.writeBuf(bufferTestP, compareSize);
	// cycleBuf.readBuf(bufferLogP, compareSize);
	// if (memcmp(bufferTestP, bufferLogP, compareSize) == 0) {
	// 	cout << "first check is OK!" << endl;
	// 	printf("test buf is\n%.*s\n\n", compareSize, bufferTestP);
	// 	printf("log buf is\n%.*s\n\n", compareSize, bufferLogP);
	// }

	// // test 2

	// int written = 0;
	// if ((written = cycleBuf.writeBuf(bufferTestP, 2048)) <= 0) cout << "Error is here" << __LINE__ << endl;
	// cout << "Written " << written << endl;
	// if ((written = cycleBuf.readBuf(bufferLogP, 4096)) <= 0) cout << "Error is here" << __LINE__ << endl;
	// cout << "Written " << written << endl;

	// bufferTestP += 1024;
	// if (memcmp(bufferTestP, bufferLogP, 2048) == 0) {
	// 	cout << "second check is OK!" << endl;
	// } else {
	// 	cout << "memcmp=" << (memcmp(bufferTestP, bufferLogP, 4096)) << endl;
	// 	// cout << "test buf is " << endl << bufferTestP;
	// 	printf("test buf is\n%.*s\n\n", 4096, bufferTestP);
	// 	printf("log buf is\n%.*s\n\n", 4096, bufferLogP);
	// 	// cout << "log buf is" << endl << bufferLogP << endl;
	// 	cout << "file content is" << endl << cycleBuf.dumpLogFile();
	// }

	remove(logName);
    return 0;
}
