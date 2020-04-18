programs := distance
objects := $(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: all clean

all: $(programs)

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

distance: distance.o
	$(CC) -o $@ $^ $(LDFLAGS) -lm -lalgc

clean:
	rm -f  $(programs) *.o