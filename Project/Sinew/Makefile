CC = gcc
XX = g++
CFLAGS = -Wall -g

TARGET = test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.cpp
	$(XX) $(CFLAGS) -c $< -o $@

OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
SOURCES = $(wildcard *.c *.cpp)

$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)

.PHONY : clean
clean :
	-rm *.o $(TARGET)
