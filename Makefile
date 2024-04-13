CXX:= g++
CXXFLAGS:= -Wall -Wextra -pedantic  -std=c++17 -O0 -g -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2
HEADERS := $(wildcard *.hh) $(wildcard *.h)

main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o