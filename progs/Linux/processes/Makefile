CC=g++
CFLAGS=-c -Wall
LDFLAGS= "-pthread"

SOURCES= main.cpp ProcessesTasks.cpp bmp_reader.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= prog
ARGS=

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o ./$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o ./$@

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -rf *.o