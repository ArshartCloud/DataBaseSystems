DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

CC = gcc
XX = g++
CFLAGS = -Wall -g
TARGET = main

BIN_TARGET = $(DIR_BIN)/$(TARGET)
SRC = $(wildcard $(DIR_SRC)/%.c $(DIR_SRC)/%.cpp)
OBJ = $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, \
		$(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ)/%.o, $(SRC)))

$(BIN_TARGET) : $(OBJ)
	$(XX) $(OBJ) -o $@

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.cpp
	$(XX) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	-rm $(DIR_OBJ)/*.o $(BIN_TARGET)

