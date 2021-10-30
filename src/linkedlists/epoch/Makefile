ROOT = ../../..

include $(ROOT)/common/Makefile.common

BINS = $(BINDIR)/epoch-lazy-list
#G++ = g++
G++ = gcc

.PHONY:	all clean

all:	main

new_urcu.o: urcu.h
	$(G++) $(CFLAGS) -c -o $(BUILDIR)/new_urcu.o new_urcu.c

linkedlist-lock.o: urcu.h
	$(G++) $(CFLAGS) -c -o $(BUILDIR)/linkedlist-lock.o linkedlist-lock.c

lazy.o: linkedlist-lock.h linkedlist-lock.o lazy.h
	$(G++) $(CFLAGS) -c -o $(BUILDIR)/lazy.o lazy.c

coupling.o: linkedlist-lock.h linkedlist-lock.o
	$(G++) $(CFLAGS) -c -o $(BUILDIR)/coupling.o coupling.c

intset.o: linkedlist-lock.h coupling.h lazy.h
	$(G++) $(CFLAGS) -c -o $(BUILDIR)/intset.o intset.c

test.o: linkedlist-lock.h coupling.h lazy.h intset.h
	$(G++) $(CFLAGS) -c -o $(BUILDIR)/test.o test.c

main: new_urcu.o linkedlist-lock.o coupling.o lazy.o intset.o test.o  urcu.h
	$(G++) $(CFLAGS) $(BUILDIR)/new_urcu.o $(BUILDIR)/linkedlist-lock.o $(BUILDIR)/lazy.o $(BUILDIR)/coupling.o $(BUILDIR)/intset.o $(BUILDIR)/test.o -o $(BINS) $(LDFLAGS)

clean:
	rm -f $(BINS)
