lib := libalgc
objects := $(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: all clean

all: $(lib).a

$(lib).a: $(objects)
	ar rc $(lib).a $(objects) 

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.a *.o