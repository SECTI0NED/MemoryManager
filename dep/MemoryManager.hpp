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
        
        
        list<MemoryBlock*> test;

    protected:
        // Local variable for the data
        list<char*> data;

        // Merge consecutive blocks if they are free in freeMBList
        void mergeBlocks();

        // Move memory blocks form allocMBList to freeMBList
        void freeMemory(int blocks);

        // For allocating memory
        virtual void allocateMemory(int blocks);

        /* Runs the Memory Manager according to how 
        many blocks are allocated and deleted while 
        there is still unallocated data */
        virtual void run(int allocate, int free);

        
        list<MemoryBlock*> allocMBList;
        list<MemoryBlock*> freedMBList;


};

#endif // MEMORY_MANAGER_H