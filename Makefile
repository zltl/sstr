.PHONY: clean build

build: sstr.c sstr.h
	gcc -I. -Wall -extra -Werror -c sstr.c

clean:
	rm -rf *.o *.gch