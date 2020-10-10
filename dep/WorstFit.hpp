#ifndef WORST_FIT_H
#define WORST_FIT_H

#include "./MemoryManager.hpp"
class WorstFit : public MemoryManager {
    public:
        WorstFit(string filename);
        ~WorstFit();
        void allocateMemory(int numberOfBlocks);
        void run(int allocate, int free);
    private:
        list<MemoryBlock*>::iterator findWorstFitBlock(int sizeRequired, bool* found);
        list<MemoryBlock*>::iterator retrieveBlock(int sizeRequired, bool* found);
};

#endif // WORST_FIT_H