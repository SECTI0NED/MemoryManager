#ifndef FIRST_FIT_H
#define FIRST_FIT_H

#include "./MemoryManager.hpp"
class FirstFit : public MemoryManager {
    public:
        FirstFit(string filename);
        ~FirstFit();
        void allocateMemory(int numberOfBlocks);
        void run(int allocate, int free);
    private:
        list<MemoryBlock*>::iterator findFirstFitBlock(int sizeRequired, bool* found);
        list<MemoryBlock*>::iterator retrieveBlock(int sizeRequired, bool* found);
};

#endif // FIRST_FIT_H