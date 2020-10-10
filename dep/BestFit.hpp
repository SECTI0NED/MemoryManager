#ifndef BEST_FIT_H
#define BEST_FIT_H

#include "./MemoryManager.hpp"
class BestFit : public MemoryManager {
    public:
        BestFit(string filename);
        ~BestFit();
        void run(int allocate, int free);
        list<MemoryBlock*>::iterator retrieveBlock(int sizeRequired, bool* found);
    private:
        list<MemoryBlock*>::iterator findBestFitBlock(int sizeRequired, bool* found);

};

#endif // BEST_FIT_H