CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic
CPPFLAGS=-I/opt/cuda/include

ifdef DEBUG
	CXXFLAGS+=-g
endif

CUOBJS=$(addprefix src/, material.o)
OBJS=$(addprefix src/, mtl_parser.o parse_tex_map.o) $(CUOBJS)
BIN=main
LIB=libmtlparser.so
LDLIBS=-ljpeg -L/opt/cuda/lib64 -lcudart

$(LIB): $(OBJS)
	nvcc --compiler-options '-fPIC' -dlink -o src/link.o $^
	$(LINK.cc) -shared -o $@ $^ src/link.o $(LDLIBS)

%.o: %.cu
	nvcc -std=c++14 -dc --compiler-options '-fPIC' -o $@ $<

$(OBJS): CXXFLAGS += -fPIC

$(BIN): $(OBJS) src/$(BIN).o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(BIN) $(OBJS) src/$(BIN).o $(LIB)

.PHONY: clean lib
