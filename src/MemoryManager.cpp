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
        Check if next block (B) exists
        If there is a next block (B)
            Check if B has cleared data
            If there B is cleared then
            Get size of B
    
    */

}

void MemoryManager::run(int allocate, int free) {

}

