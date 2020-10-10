#ifndef WORST_FIT_H
#define WORST_FIT_H

#include "./MemoryManager.hpp"
class WorstFit : public MemoryManager {
    public:
        WorstFit(string filename);
        ~WorstFit();
        void run(int allocate, int free);
        list<MemoryBlock*>::iterator retrieveBlock(int sizeRequired, bool* found);
    private:
        list<MemoryBlock*>::iterator findWorstFitBlock(int sizeRequired, bool* found);
 
};

#endif // WORST_FIT_H