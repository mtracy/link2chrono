TARGET = prog
CC=g++
EXT=cpp
CFLAGS=-I$(IDIR)
STD=c++14

IDIR=include
SDIR=src
ODIR=src/obj
LDIR=lib

LIBS=-lboost_system -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst $(SDIR)/%.$(EXT), $(ODIR)/%.o, $(wildcard $(SDIR)/*.$(EXT)))
HEADERS = $(wildcard $(IDIR)/*.h)

$(ODIR)/%.o: src/%.cpp $(HEADERS)
	$(CC) -g -std=$(STD) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -g -std=$(STD) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(ODIR)/*.o
	-rm -f $(TARGET)