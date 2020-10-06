#include "../dep/MemoryManager.hpp"

MemoryManager::MemoryManager() {}
MemoryManager::~MemoryManager() {}


MemoryManager::MemoryManager(string filename) {
    ifstream stream(filename);
    string line = "";
    while(!stream.eof()){
        stream >> line; 
        // char cstring[line.size()];
        // strcpy(cstring, line.c_str());
        dataList.push_back(line); 
    }
    stream.close();
}


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

        /* Remove the block from the allocMBList 
        and reduce the amount of blocks to free*/
        allocMBList.pop_front();
        numberOfBlocks-=1;
    }
    cout << "Freed:" << endl;
    for(MemoryBlock* mb : freedMBList){
        cout << mb->getId() << " ";
    }
    cout << endl;
    /* Merge adjacent blocks */
    mergeBlocks();
}


// For merging adjacent free blocks in freedMBList
void MemoryManager::mergeBlocks() {

    list<MemoryBlock*>::iterator currentBlockPtr = freedMBList.begin();
    list<MemoryBlock*>::iterator nextBlockPtr = freedMBList.end();

    while((*currentBlockPtr) != freedMBList.back()){
        nextBlockPtr = currentBlockPtr;
        nextBlockPtr++;
        if((*currentBlockPtr)->isFree()){
            cout << "Current block is free" << endl;
            if((*nextBlockPtr)->isFree()) {
                cout << "Next block is free" << endl;
                cout << "CurrentBlock ID: " << (*currentBlockPtr)->getId() << endl;
                // Retrieve the new size of the memory block
                int currentBlockSize = (*currentBlockPtr)->getSize();
                int nextBlockSize = (*nextBlockPtr)->getSize();
                int newSize = currentBlockSize + nextBlockSize;

                /* Reset the data to null and request a new memory 
                chunk with the new size (not necessary, but it's 
                better than having the both the memory blocks' old 
                data mixed togeher) */
           
                char data[newSize] = {0};
                void* request = sbrk(newSize);
                strcpy((char*) request, data);

                /* Set the current block's new size and data*/
        
                (*currentBlockPtr)->setSize(newSize);
                (*currentBlockPtr)->setData((char*) request);
                (*currentBlockPtr)->clearData();
                (*currentBlockPtr)->setStartingAddress((char**) request);

                // Erase the next block
                cout << "NextBlock ID: "<< (*nextBlockPtr)->getId() << endl;
                freedMBList.erase(nextBlockPtr);

                // Reset the next block pointer
                nextBlockPtr = freedMBList.end();
            }
        } else {
            cout << "Current block is NOT free" << endl;
            currentBlockPtr = nextBlockPtr;
        }
    }
}

void MemoryManager::run(int allocate, int free) {

}

