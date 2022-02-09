.PHONY:

build: sstr.c sstr.h
	gcc -I. -Wall -extra -Werror -c sstr.c

