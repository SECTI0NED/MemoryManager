#ifndef FIRST_FIT_H
#define FIRST_FIT_H

#include "./MemoryManager.hpp"
class FirstFit : public MemoryManager {
    public:
        FirstFit(string filename);
        ~FirstFit();
        void allocateMemory(int blocks);
        void run(int allocate, int free);
};

#endif // FIRST_FIT_H