sub_name = example

sources_c = $(wildcard *.c)
objs_c = $(patsubst %.c,$(TARGET_DIR)/$(sub_name)/%.c.o,$(sources_c))
$(shell mkdir -p $(TARGET_DIR)/$(sub_name))

all: $(objs_c)

$(TARGET_DIR)/$(sub_name)/%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
