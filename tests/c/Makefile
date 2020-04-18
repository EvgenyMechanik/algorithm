programs := distance
objects := $(patsubst %.c,%.o,$(wildcard *.c))
vpath %.a $(ROOT_DIR)/c

.PHONY: all clean

all: $(programs)

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

distance: distance.o -lalgc
	$(CC) -o $@ $^ $(LDFLAGS) -lm -lalgc

clean:
	rm -f  $(programs) *.o