CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic

ifdef DEBUG
	CXXFLAGS+=-g
endif

OBJS=$(addprefix src/, parser.o parse_tex_map.o)
BIN=main
LIB=libmtlparser.so
LDLIBS=-ljpeg


$(LIB): $(OBJS)
	$(LINK.cc) -shared -o $@ $^ $(LDLIBS)

$(OBJS): CXXFLAGS += -fPIC

$(BIN): $(OBJS) src/$(BIN).o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(BIN) $(OBJS) src/$(BIN).o $(LIB)

.PHONY: clean lib
