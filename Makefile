CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic
CPPFLAGS=-I/opt/cuda/include
CUFLAGS= -std=c++14

ifdef DEBUG
	CXXFLAGS+=-g
endif

CUOBJS=$(addprefix src/, material.o)
OBJS=$(addprefix src/, parser.o parse_tex_map.o) $(CUOBJS)
BIN=main
LIB=libmtlparser.so
LDLIBS=-ljpeg -L/opt/cuda/lib64 -lcudart

%.o: %.cu
	nvcc $(CUFLAGS) -o $@ -dc --compiler-options '-fPIC' $<

$(LIB): $(OBJS)
	$(LINK.cc) -shared -o $@ $^ $(LDLIBS)

$(OBJS): CXXFLAGS += -fPIC

$(BIN): $(OBJS) src/$(BIN).o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(BIN) $(OBJS) src/$(BIN).o $(LIB)

.PHONY: clean lib
