sub_name = test

sources_c = $(wildcard *.c)
sources_cc = $(wildcard *.cc)
objs_c = $(patsubst %.c,$(TARGET_DIR)/$(sub_name)/%.c.o,$(sources_c))
objs_cc = $(patsubst %.cc,$(TARGET_DIR)/$(sub_name)/%.cc.o,$(sources_cc))
objs_sstr = $(TARGET_DIR)/sstr.c.o

$(shell mkdir -p $(TARGET_DIR)/$(sub_name))

all: $(TARGET_DIR)/$(sub_name)/unit_test

$(TARGET_DIR)/$(sub_name)/%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(TARGET_DIR)/$(sub_name)/%.cc.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_DIR)/$(sub_name)/unit_test: $(objs_c) $(objs_cc) $(objs_sstr)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ -lgtest -lgtest_main -lpthread
