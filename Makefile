EXE	= project1b

all: project1b

project1b: hash24.o dictionary.o pa1b.o
	g++ -std=c++11 $^ -o $@

clean:
	rm -rf ${EXE}