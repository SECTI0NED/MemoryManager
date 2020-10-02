#include "../dep/MemoryManager.hpp"

MemoryManager::MemoryManager() {}
MemoryManager::~MemoryManager() {}
MemoryManager::MemoryManager(list<char*>* data) {}


void MemoryManager::allocateMemory(int blocks) {
    // Each Memory Manager will have its own implementation of allocateMemory().
}

void MemoryManager::freeMemory(int blocks) {
    int numberOfBlocks = blocks;
    while(numberOfBlocks > 0){
        /* Get the memory block from allocMBList */
        MemoryBlock* memoryBlock = allocMBList.front();
        
        /* Clear the data while maintaining the size. */
        memoryBlock->clearData();

        /* Add this block to the freedMBList*/
        freedMBList.push_back(memoryBlock);
        
        /* Merge adjacent blocks */
        mergeBlocks();

        /* Remove the block from the allocMBList 
        and reduce the amount of blocks to free*/
        allocMBList.pop_front();
        numberOfBlocks-=1;
    }
}

void MemoryManager::mergeBlocks() {
    /*
        BlockPtr = first block (A)
        NextBlockPtr = nullptr

        while(BlockPtr != lastBlock in freedMBList)
        NextBlockPtr = NextBlock (B)
            If there B is cleared then
                Get size of B (bsize)
                Get size of A (asize)
                Let size = (asize += bsize)
                Let data = char[asize] = {'\0'}
                void* request = sbrk(size) // GET NEW REQUEST WITH NEW A SIZE
                strcpy((char*) request, data); // COPY DATA INTO REQUEST
                Set A->size = size
                Set A->data = (char*) request
                Set A->startingaddress = (char**) request
                Remove B from freedMBList
                NextBlockPtr = nullptr
                BlockPtr = A

    
    */

}

void MemoryManager::run(int allocate, int free) {

}

