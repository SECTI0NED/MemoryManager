/* 
    Class for representing Memoey
*/
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "./MemoryBlock.hpp"

class MemoryManager {
    public:
        MemoryManager();
        MemoryManager(string filename);
        virtual ~MemoryManager();

        /* Runs the Memory Manager according to how 
        many blocks are allocated and deleted while 
        there is still unallocated data */
        virtual void run(int allocate, int free);

        virtual list<MemoryBlock*>::iterator retrieveBlock(int sizeRequired, bool* found);
     

    protected:
        // Number of times blocks were merged in freedMBList
        int mergeTotal;
        
        // Number of times blocks were split in freedMBList
        int splitTotal;

        // Total emmory allocated by sbrk in allocMBList
        int sbrkTotal;

        list<MemoryBlock*> allocMBList;
        list<MemoryBlock*> freedMBList;

        // Local variable for the data
        list<string> dataList;

        // Merge consecutive blocks if they are free in freeMBList
        void mergeBlocks();

        // Split block if its size meets its required data size
        MemoryBlock* splitBlock(list<MemoryBlock*>::iterator memoryBlockIter, int size);

        // For allocating memory
        void allocateMemory(int numberOfBlocks);

        // Move memory blocks form allocMBList to freeMBList
        void freeMemory(int numberOfBlocks);
        
        // For printing details to file
        void printDetails(string filename, string managerTypeLabel);

        // For printing details to console
        void printDetailsConsole(string filename, string managerTypeLabel);

        // Name of the file for the data
        string dataSourceFile;
};

#endif // MEMORY_MANAGER_H