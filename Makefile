all: build/main.o build/cycle_buf.o
	g++ -g -o build/cycle_buf build/cycle_buf.o build/main.o

main.o: main.cc
	g++ -g -o build/main.o -c build/main.cc

cycle_buf.o: cycle_buf.cc
	g++ -g -o build/cycle_buf.o -c build/cycle_buf.cc
