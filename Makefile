EXE = gravity-app

all: $(EXE)

CC = g++
LIB = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -g -c -Wall -std=c++17
LFLAGS = 

OBJ = build/*.o
SRC = src/*.cpp

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LFLAGS) $(LIB)

$(OBJ): $(SRC) src/planet.hpp
	$(CC) $(CFLAGS) $(SRC)
	mv *.o build/

clean:
	rm -f $(OBJ) $(EXE)

