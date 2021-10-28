ROOT = ../../..

include $(ROOT)/common/Makefile.common

BINS = $(BINDIR)/smart-pointer-lazy-list
#CFLAGS += -std=gnu89
C++ = g++

.PHONY:	all clean

all:	main

linkedlist-lock.o: 
	$(C++) $(CFLAGS) -c -o $(BUILDIR)/linkedlist-lock.o linkedlist-lock.c

lazy.o: linkedlist-lock.h linkedlist-lock.o
	$(C++) $(CFLAGS) -c -o $(BUILDIR)/lazy.o lazy.c	 

coupling.o: linkedlist-lock.h linkedlist-lock.o
	$(C++) $(CFLAGS) -c -o $(BUILDIR)/coupling.o coupling.c

intset.o: linkedlist-lock.h coupling.h lazy.h
	$(C++) $(CFLAGS) -c -o $(BUILDIR)/intset.o intset.c

test.o: linkedlist-lock.h coupling.h lazy.h intset.h
	$(C++) $(CFLAGS) -c -o $(BUILDIR)/test.o test.c

main: linkedlist-lock.o coupling.o lazy.o intset.o test.o
	$(C++) $(CFLAGS) $(BUILDIR)/linkedlist-lock.o $(BUILDIR)/lazy.o $(BUILDIR)/coupling.o $(BUILDIR)/intset.o $(BUILDIR)/test.o -o $(BINS) $(LDFLAGS)

clean:
	rm -f $(BINS)
