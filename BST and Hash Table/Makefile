CC = g++
CFLAGS = -c -g
DEPS = BST.h HashTable.h FolderTraversal.h
LDFLAGS=
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) *.cpp

clean:
	rm $(EXCUTABLE) $(OBJECTS)
