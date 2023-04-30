CC=nvcc
CFLAGS=-c -Wall
LDFLAGS=

SOURCES= main.cpp CudaTasks.cu bmp_reader.cpp
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