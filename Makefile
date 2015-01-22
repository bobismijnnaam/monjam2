# Maek

FLAGS = -lpng -ljpeg -lz -lpthread -lmingw32 -I JPEGReaderWriter-1.0.1 -I pngpp -I mingw-std-threads -std=c++11 -g

SOURCES = $(wildcard *.cpp) $(wildcard ./JPEGReaderWriter-1.0.1/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: monjam

monjam: $(OBJECTS)
	g++ $(OBJECTS) $(FLAGS) -o monjam2

%.o: %.cpp
	g++ -c $(FLAGS) $< -o $@ 
