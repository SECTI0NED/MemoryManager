/* 
    Class for representing Memoey
*/
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "./MemoryBlock.hpp"

class MemoryManager {
    public:
        MemoryManager();
        ~MemoryManager();
        virtual void allocateMemory();
        list<MemoryBlock*> allocMBList;

    private:
        // list<MemoryBlock*> allocMBList;
        // list<MemoryBlock*> freedMBList;


};

#endif // MEMORY_MANAGER_H