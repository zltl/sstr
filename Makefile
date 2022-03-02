.PHONY: clean example objs doxygen
.ONESHELL:

TARGET_DIR ?=

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
ifeq ($(TARGET_DIR),)
	TARGET_DIR = $(ROOT_DIR)/target
endif
$(shell mkdir -p $(TARGET_DIR))
SANITIZER_FLAGS = -fsanitize=address -lasan
CFLAGS ?= -Wall -Wextra -Werror -std=c11 -ggdb -I$(ROOT_DIR) $(SANITIZER_FLAGS)
LDFLAGS ?=

export

all: objs example

example: $(TARGET_DIR)/example/example

objs: $(TARGET_DIR)/example/%.c.o $(TARGET_DIR)/sstr.c.o

$(TARGET_DIR)/example/%.c.o: $(wildcard $(TARGET_DIR)/example/*.c)
	$(MAKE) -C $(ROOT_DIR)/example
$(TARGET_DIR)/sstr.c.o: sstr.h sstr.c
	$(CC) $(CFLAGS) -c sstr.c -o $@

$(TARGET_DIR)/example/example: $(TARGET_DIR)/example/example.c.o $(TARGET_DIR)/sstr.c.o
	gcc $^ -o $@ $(LDFLAGS) $(CFLAGS)

clean:
	rm -rf $(TARGET_DIR)

doxygen:
	if [ ! -d target/doxygen-awesome-css ]; then
		mkdir -p target
		git clone --depth=1 git@github.com:jothepro/doxygen-awesome-css.git target/doxygen-awesome-css
	fi
	doxygen doxygen/Doxyfile
	mkdir -p docs
	cp -rf doc/html/* docs/
