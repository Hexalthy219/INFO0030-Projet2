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
OBJECTS=main.o filtre.o

# Documentation
DOC=pnm.c filtre.c pnm.h filtre.h

# Librairie

AR=ar
RANLIB=ranlib
LIBFILE=lib


## Rules

all: $(EXEC)

filtre: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) -L $(LIBFILE) -lpnm $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

filtre.o: filtre.c
	$(CC) -c filtre.c -o filtre.o $(CFLAGS)

doc:all_doc clean_latex

all_doc: $(DOC)
	doxygen $(DOC)
	mkdir -p doc
	mv html doc/html
	mv latex doc/latex

clean_latex:
	rm -r doc/latex/

clean_doc:
	rm -r doc

lib: libpnm.a
	mkdir -p lib
	mv libpnm.a lib/libpnm.a

libpnm.a:pnm.o
	$(AR) ruv $@ $?
	$(RANLIB) $@

clean_lib:
	rm -r lib/

archive:
	tar -zcvf filtres.tar.gz *.c *.h Makefile doc lib 

clean:
	rm -f *.o $(EXEC) *~ test.*

