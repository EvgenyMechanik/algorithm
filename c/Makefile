objects := $(patsubst %.c,%.o,$(wildcard *.c))
all: $(objects)
$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@