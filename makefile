# Compiler to use
CC = g++

# Compiler flags
SFMLDEPS = -lsfml-audio-d -lsfml-graphics-d -lsfml-system-d -lsfml-window-d

# Source files
SOURCES = src/main.cpp

# Target file
TARGET = Sierpinski-triangle

all:
	if [ ! -d "./build" ]; then \
		mkdir ./build; \
	fi
	$(CC) $(SOURCES) -c && $(CC) $(SFMLDEPS) main.o -o build/$(TARGET)

run: all
	./build/$(TARGET)

clean:
	$(RM) -r main.o build