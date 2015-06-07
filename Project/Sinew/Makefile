test : catalog.o my_string.o serial.o write.o my_vector.o read.o test.o
	g++ catalog.o my_string.o serial.o write.o my_vector.o read.o test.o -o test
test.o :
	g++ -c test.cpp
catalog.o :
	g++ -c catalog.cpp
my_string.o :
	g++ -c my_string.cpp
my_vector.o :
	g++ -c my_vector.cpp
serial.o :
	g++ -c serial.cpp
write.o :
	g++ -c write.cpp
read.o :
	g++ -c read.cpp
clean:
	rm *.o test
