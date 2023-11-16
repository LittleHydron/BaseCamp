CXX = gcc
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lstdc++

SNIFFER_OBJS = obj/sniffer.o obj/main.o

all: bin/sniffer

bin/sniffer: $(SNIFFER_OBJS) | bin
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/sniffer/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/main.o: src/main.cpp | obj
	$(CXX) $(CXXFLAGS) -Isrc/sniffer -c -o $@ $<

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -f bin/sniffer $(SNIFFER_OBJS)

.PHONY: all clean
