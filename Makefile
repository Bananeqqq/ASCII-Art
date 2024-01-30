CXX := g++
CFLAGS := -std=c++17 `sdl2-config --libs --cflags` -Wall -Wextra -pedantic -O2 -g -MMD
LIBS := -lpng -ljpeg `sdl2-config --libs` -lSDL2_ttf -lSDL2_image

INCLUDES := -I/usr/include -I/usr/include/SDL2
LIB_DIRS := -L/usr/lib -L/usr/lib/x86_64-linux-gnu

SRC_DIR := src
BUILD_DIR := obj

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE := app
TEST_SCRIPT := assets/test.sh


.PHONY: all compile run asan doc test clean

all: compile doc

compile: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)


ASAN_CFLAG := -fsanitize=address
asan: CFLAGS += $(ASAN_CFLAG)
asan: clean $(EXECUTABLE)

doc:
	doxygen Doxyfile

test: compile
	chmod +x $(TEST_SCRIPT)
	./$(TEST_SCRIPT)


$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDES) $(LIB_DIRS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE) doc

-include $(OBJECTS:.o=.d)
