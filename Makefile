CC = g++
CFLAGS = -Wall -Werror -Wno-deprecated -std=c++11 -O

DDIR = dep
ODIR = obj
SDIR = src


_DEP = Utils.hpp main.hpp MemoryManager.hpp MemoryBlock.hpp FirstFit.hpp BestFit.hpp WorstFit.hpp
DEP = $(patsubst %, $(DDIR)/%, $(_DEP))

_OBJ = main.o MemoryManager.o MemoryBlock.o FirstFit.o BestFit.o WorstFit.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: program

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f program $(ODIR)/*.o