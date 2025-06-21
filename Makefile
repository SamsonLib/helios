CXX = g++
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/objects/%.o)
OUT = app.out
BIN = build/$(OUT)

all: build

build: $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(FLA)

build/objects/%.o: src/%.cpp
	mkdir -p build/objects
	$(CXX) -c $< -o $@

run: build
	./$(BIN)

clean:
	rm -rf build

.PHONY: all build shared run clean
