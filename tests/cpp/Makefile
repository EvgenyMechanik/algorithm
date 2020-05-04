programs := polynom hanoi sort
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
vpath %.a $(ROOT_DIR)/cpp

.PHONY: all clean

all: $(programs)

$(objects): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

polynom: polynom.o -lalgcpp
	$(CXX) -o $@ $^ $(LDFLAGS) -lalgcpp

hanoi: hanoi.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

sort: sort.o -lalgcpp
	$(CXX) -o $@ $^ $(LDFLAGS) -lalgcpp

clean:
	rm -f  $(programs) *.o