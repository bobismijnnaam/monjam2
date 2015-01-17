# Maek

FLAGS = -lpng -ljpeg -lz -I ./JPEGReaderWriter-1.0.1 -I ./pngpp -std=c++11 -g

SOURCES = $(wildcard *.cpp) $(wildcard ./JPEGReaderWriter-1.0.1/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: monjam

monjam: $(OBJECTS)
	g++ $(OBJECTS) $(FLAGS) -o monjam 

%.o: %.cpp
	g++ -c $(FLAGS) $< -o $@ 
