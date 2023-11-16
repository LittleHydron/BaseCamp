CXX = gcc
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lstdc++

SNIFFER_OBJS = obj/sniffer.o obj/main.o

all: bin/sniffer

bin/sniffer: $(SNIFFER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/sniffer/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -Isrc/sniffer -c -o $@ $<

clean:
	rm -f bin/sniffer $(SNIFFER_OBJS)

.PHONY: all clean
