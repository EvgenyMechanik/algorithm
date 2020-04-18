lib := libalgcpp
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

.PHONY: all clean

all: $(lib).a

$(lib).a: $(objects)
	ar rc $(lib).a $(objects) 

$(objects): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.a *.o