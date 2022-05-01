# -*- Makefile -*-
#  Veronika Molnarova, FIT
#  IJC, DU-2

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

EXECUTABLE = tail wordcount wordcount-dynamic libhtab.a libhtab.so
OBJC = htab_for_each.o htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_move.o htab_size.o

#build always
all: $(EXECUTABLE)

# -------executables---------

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static -o $@ $^

wordcount-dynamic: wordcount-dynamic.o io.o libhtab.so
	LD_LIBRARY_PATH="."
	$(CC) $(CFLAGS) wordcount-dynamic.o io.o -L . -lhtab -Wl,-rpath="$(PWD)" -o $@

# --------libraries------------

libhtab.a: $(OBJC)
	ar rc $@ $^

libhtab.so: $(OBJC)
	LD_LIBRARY_PATH="."
	$(CC) -shared -fPIC $^ -o $@

# -------all object files-------

wordcount-dynamic.o: wordcount.c htab.h io.h
	$(CC)  $(CFLAGS) -fPIC -c $< -o $@

wordcount.o: wordcount.c htab.h io.h
	$(CC)  $(CFLAGS) -c $< -o $@

io.o: io.c io.h
	$(CC)  $(CFLAGS) -c $< -o $@

%.o: %.c private.h # prelozi vsetky htab.c subory
	$(CC)  $(CFLAGS) -c $< -fPIC


# ------tail funcion--------

tail: tail.o
	$(CC)  $(CFLAGS) $^ -o $@
tail.o: tail.c
	$(CC)  $(CFLAGS) -c $^ -o $@

# --------cleaning-----------
clean:
	rm -f *.o $(EXECUTABLE)
