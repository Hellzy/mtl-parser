CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic
CUFLAGS=-std=c++14
CPPFLAGS=-I/opt/cuda/include

ifdef DEBUG
	CXXFLAGS+=-O0 -g
	CUFLAGS+=-O0 -g
endif

CUOBJS=$(addprefix src/, material.o)
OBJS=$(addprefix src/, mtl_parser.o parse_tex_map.o) $(CUOBJS)
BIN=main
LIB=libmtlparser.so
LDLIBS=-ljpeg -L/opt/cuda/lib64 -lcudart

$(LIB): $(OBJS)
	nvcc $(CUFLAGS) --compiler-options '-fPIC' -dlink -o src/link.o $^
	$(LINK.cc) -shared -o $@ $^ src/link.o $(LDLIBS)

%.o: %.cu
	nvcc $(CUFLAGS) -dc --compiler-options '-fPIC' -o $@ $<

$(OBJS): CXXFLAGS += -fPIC

$(BIN): $(OBJS) src/$(BIN).o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(BIN) $(OBJS) src/$(BIN).o $(LIB)

.PHONY: clean lib
