CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS =

ifeq ($(OS), Windows_NT)
    LDFLAGS += -lws2_32
else
	LDFLAGS += -lX11
endif
CLIENT_OBJS = obj/client.o obj/Connection.o obj/TrackMouse.o
SERVER_OBJS = obj/server.o obj/Connection.o obj/TrackMouse.o

all: bin/client bin/server

bin/client: $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

bin/server: $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/network/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/platform/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -Isrc/network -Isrc/platform -c -o $@ $<

clean:
	rm -f bin/client bin/server $(CLIENT_OBJS) $(SERVER_OBJS)

.PHONY: all clean
