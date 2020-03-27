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
DOC=main.c pnm.c filtre.c pnm.h filtre.h

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

doc_and_clear:doc clean_doc

doc: 
	doxygen $(DOC)
	cd latex && make
	cd ..
	mkdir doc
	mv latex/refman.pdf doc/documentation.pdf

clean_doc:
	rm -r html/ latex/

lib: libpnm.a
	[ ! -f "lib" ] && mkdir lib
	mv libpnm.a lib/libpnm.a

libpnm.a:pnm.o
	$(AR) ruv $@ $?
	$(RANLIB) $@

clean_lib:
	rm -r lib/

clean:
	rm -f *.o $(EXEC) *~ test.*

