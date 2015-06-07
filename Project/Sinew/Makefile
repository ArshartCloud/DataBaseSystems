objects = catalog.o my_string.o serial.o write.o read.o test.o

test : $(objects)
	g++ $(objects) -g -o test

.PHONY : clean
clean :
	rm *.o test
