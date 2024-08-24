CXX = g++
CXXFLAGS = -std=c++17

INCLUDES = -Isrc/includes -I/usr/include/jsoncpp

SRC_FILES = src/main.cpp src/screenshot.cpp src/upload.cpp src/input.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

TARGET = cmdX

LIBS = -lcurl -ljsoncpp -lX11 -lXtst

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: clean

