CC = g++

CFLAGS = -std=c++14 -m64 -Wall

SRC_DIR = src/*.cpp
OBJ_DIR = *.o

EXE_DIR = bin
EXE_NAME = MicroJumper

LIBS = -lraylib -lGL -ldl -lrt -lpthread -lX11

all:
	cp -r res $(EXE_DIR)
	$(CC) -c $(SRC_DIR) $(CFLAGS)
	$(CC) $(OBJ_DIR) -o $(EXE_DIR)/$(EXE_NAME) $(LIBS)
	rm -rf $(OBJ_DIR)
	./$(EXE_DIR)/$(EXE_NAME)

build:
	cp -r res $(EXE_DIR)
	$(CC) -c $(SRC_DIR) $(CFLAGS)
	$(CC) $(OBJ_DIR) -o $(EXE_DIR)/$(EXE_NAME) $(LIBS)
	rm -rf $(OBJ_DIR)

run:
	./$(EXE_DIR)/$(EXE_NAME)
