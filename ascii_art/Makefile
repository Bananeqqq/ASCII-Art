CXX := g++
CFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2 -g
LIBS := -lpng -ljpeg

INCLUDES := -I/path/to/libpng/include -I/path/to/libjpeg/include
LIB_DIRS := -L/path/to/libpng/lib -L/path/to/libjpeg/lib

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE := $(BIN_DIR)/ascii_art



.PHONY: all compile run asan valgrind clean

all: compile run

compile: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)


ASAN_CFLAG := -fsanitize=address
asan: CFLAGS += $(ASAN_CFLAG)
asan: clean $(EXECUTABLE)
	  ./$(EXECUTABLE)

valgrind: clean $(EXECUTABLE)
		  valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CFLAGS) $(INCLUDES) $(LIB_DIRS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
