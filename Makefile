EXE = build/gravity-app

all: $(EXE)

# Install SFML to 'sfml' directory. Copy 'bin', 'lib' and 'include' into there.
# Also add 'sfml/bin' to path.

CC = g++
LIB = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -g -c -Wall -std=c++17 -Isfml/include
LFLAGS = -Lsfml/bin -Lsfml/lib

OBJ = build/*.o
SRC = src/*.cpp

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LFLAGS) $(LIB)

$(OBJ): $(SRC) src/planet.hpp
	$(CC) $(CFLAGS) $(SRC)
	mv *.o build/

clean:
	rm -f $(OBJ) $(EXE)

