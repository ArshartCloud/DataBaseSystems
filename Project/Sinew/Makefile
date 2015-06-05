test : test.o my_string.o read.o

test.o : test.cpp my_string.h read.h
	g++ -c -g test.cpp
read.o : read.h read.cpp serial.h my_vector.cpp
	g++ -c -g read.cpp my_vector.cpp serial.cpp
my_string.o : my_string.h my_string.cpp
	g++ -c -g my_string.cpp
clean:
	rm *.o
