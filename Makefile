all: main.o cycle_buf.o
	g++ -g -o build/cycle_buf build/cycle_buf.o build/main.o

main.o: main.cc
	g++ -g -o build/main.o -c main.cc

cycle_buf.o: cycle_buf.cc
	g++ -g -o build/cycle_buf.o -c cycle_buf.cc
