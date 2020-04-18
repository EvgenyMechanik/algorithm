programs := polynom
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

.PHONY: all clean

all: $(programs)

$(objects): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

polynom: polynom.o
	$(CXX) -o $@ $^ $(LDFLAGS) -lm -lalgcpp

clean:
	rm -f  $(programs) *.o