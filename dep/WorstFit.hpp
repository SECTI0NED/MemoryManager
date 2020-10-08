#ifndef WORST_FIT_H
#define WORST_FIT_H

#include "./MemoryManager.hpp"
class WorstFit : public MemoryManager {
    public:
        WorstFit(string filename);
        ~WorstFit();
        void allocateMemory(int numberOfBlocks);
        void run(int allocate, int free);
};

#endif // WORST_FIT_H