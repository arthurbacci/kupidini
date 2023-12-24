KUPIDINI_LIBS=-I../
KUPIDINI_DEV=-Wall -pedantic --std=c89

all: clean test

test: *.c ../kupidini.c
	$(CC) -o test $^ $(CFLAGS) $(LDFLAGS) $(KUPIDINI_LIBS) $(LIBS) $(LD_LIBS)

dev: *.c ../kupidini.c
	$(CC) -o test $^ $(KUPIDINI_DEV) $(CFLAGS) $(LDFLAGS) $(KUPIDINI_LIBS) $(LIBS) $(LD_LIBS)

asan: *.c ../kupidini.c
	$(CC) -o test $^ -fsanitize=address $(KUPIDINI_DEV) $(CFLAGS) $(LDFLAGS) $(KUPIDINI_LIBS) $(LIBS) $(LD_LIBS)

ubsan: *.c ../kupidini.c
	$(CC) -o test $^ -fsanitize=undefined $(KUPIDINI_DEV) $(CFLAGS) $(LDFLAGS) $(KUPIDINI_LIBS) $(LIBS) $(LD_LIBS)

clean:
	rm -f test *.o

