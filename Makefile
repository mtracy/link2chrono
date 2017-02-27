TARGET = prog
CC=g++
EXT=cpp
CFLAGS=-I$(IDIR)
STD=c++14

IDIR=include
TMXDIR=/home/mitchell/apps/sfml-tmxloader
SDIR=src
ODIR=src/obj
LDIR=lib

LIBS=-lboost_system -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lz
SOLIBS=-L/home/mitchell/apps/sfml-tmxloader -ltmx-loader -lpugi
# L/home/mitchell/apps/sfml-tmxloader
.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst $(SDIR)/%.$(EXT), $(ODIR)/%.o, $(wildcard $(SDIR)/*.$(EXT)))
HEADERS = $(wildcard $(IDIR)/*.h) $(wildcard $(TMXDIR)/tmx/*.h) $(wildcard $(IDIR)/pugixml/*.h) 

$(ODIR)/%.o: src/%.cpp $(HEADERS)
	$(CC) -g -std=$(STD) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ -g -std=$(STD) $(OBJECTS) -Wall $(SOLIBS) $(LIBS)

clean:
	-rm -f $(ODIR)/*.o
	-rm -f $(TARGET)