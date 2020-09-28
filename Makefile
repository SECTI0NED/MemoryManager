CC = g++
CFLAGS = -Wall -Werror -std=c++11 -O

DDIR = dep
ODIR = obj
SDIR = src


_DEP = Types.hpp main.hpp MemoryManager.hpp MemoryBlock.hpp FirstFit.hpp
DEP = $(patsubst %, $(DDIR)/%, $(_DEP))

_OBJ = main.o Memory.o MemoryBlock.o FirstFit.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: program

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f program $(ODIR)/*.o