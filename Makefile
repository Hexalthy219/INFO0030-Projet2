### 
## Makefile
## INFO0030: Projet 2
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=

# Files
EXEC=filtre
MODULES=main.c pnm.c filtre.c
OBJECTS=main.o pnm.o filtre.o

## Rules

all: $(EXEC)

filtre: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

filtre.o: filtre.c
	$(CC) -c filtre.c -o filtre.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

