programs := distance fractal pack
objects := $(patsubst %.c,%.o,$(wildcard *.c))
vpath %.a $(ROOT_DIR)/c

.PHONY: all clean

all: $(programs)

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

distance: distance.o -lalgc
	$(CC) -o $@ $^ $(LDFLAGS) -lm -lalgc

fractal: fractal.o
	$(CC) -o $@ $^ $(LDFLAGS) -lX11 -lm

pack: pack.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f  $(programs) *.o