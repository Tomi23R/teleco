CC=gcc
CFLAGS=-c -Wall
SOURCES=nslookup.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=nslookup

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	@echo -n compilando el Ejecutable \'$@\' ...
	@$(CC) $(OBJECTS) -o $@
	@echo [OK]

.c.o:
	@echo -n compilando Objeto \'$<\' ...
	@$(CC) $(CFLAGS) $< -o $@
	@echo [OK]

clean:
	@echo -n limpiando proyecto ...
	@rm -f $(wildcard *.o *.d core* *.P) $(EXECUTABLE)
	@echo [OK]
entrega:
	@echo -n comprimiendo proyecto ... 
	@tar -zcvf entrega.tgz *.c Makefile
	@echo [OK]
