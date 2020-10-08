#ifndef BEST_FIT_H
#define BEST_FIT_H

#include "./MemoryManager.hpp"
class BestFit : public MemoryManager {
    public:
        BestFit(string filename);
        ~BestFit();
        void allocateMemory(int numberOfBlocks);
        void run(int allocate, int free);
};

#endif // BEST_FIT_H