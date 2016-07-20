
all: sqlitelib.o libsqlitelib.so test.o

sqlitelib.o: sqlitelib.c
	@gcc -c -Wall -Werror -fpic sqlitelib.c

libsqlitelib.so: sqlitelib.o
	@gcc -shared -o libsqlitelib.so sqlitelib.o

test.o: test.c
	@gcc -L./  -o test.o test.c -lsqlitelib -lsqlite3 

.PHONY: all clean
clean:
	@rm -rf *.o
	@rm -rf *.so
	@rm -rf *.db

