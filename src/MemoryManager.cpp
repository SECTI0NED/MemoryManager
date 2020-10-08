#include "../dep/MemoryManager.hpp"
#include <random>

MemoryManager::MemoryManager() {}
MemoryManager::~MemoryManager() {}


MemoryManager::MemoryManager(string filename) {
    ifstream stream(filename);
    string line = "";
    while(!stream.eof()){
        stream >> line; 
        dataList.push_back(line); 
    }
    stream.close();
}

void MemoryManager::run(int allocate, int free) {
    // Each Memory Manager will have its own implementation of run().
}

void MemoryManager::allocateMemory(int numberOfBlocks) {
    // Each Memory Manager will have its own implementation of allocateMemory().
}

// Need to select random block from allocMBList
void MemoryManager::freeMemory(int numberOfBlocks) {
    if(numberOfBlocks <= (int) allocMBList.size()){
        while(numberOfBlocks > 0){
        list<MemoryBlock*>::iterator randomPosition = allocMBList.begin();
        int random = rand() % allocMBList.size();
        std::advance(randomPosition, random);
        /* Get the memory block from allocMBList */
        MemoryBlock* memoryBlock = (*randomPosition);
        
        /* Clear the data while maintaining the size. */
        memoryBlock->clearData();

        /* Add this block to the freedMBList*/
        freedMBList.push_back(memoryBlock);

        /* Remove the block from the allocMBList 
        and reduce the amount of blocks to free*/
        allocMBList.pop_front();
        numberOfBlocks-=1;
        }

        /* Merge adjacent blocks */
        mergeBlocks();
    } else {
        cout << "Error number of blocks requested to be freed: " << numberOfBlocks << endl
        << "Number of names in data list: " << dataList.size() << endl;
    }
    
}


// For merging adjacent free blocks in freedMBList
void MemoryManager::mergeBlocks() {

    list<MemoryBlock*>::iterator currentBlockPtr = freedMBList.begin();
    list<MemoryBlock*>::iterator nextBlockPtr = freedMBList.end();

    while((*currentBlockPtr) != freedMBList.back()){
        nextBlockPtr = currentBlockPtr;
        nextBlockPtr++;
        if((*currentBlockPtr)->isFree()){
            if((*nextBlockPtr)->isFree()) {

                // Retrieve the new size of the memory block
                int currentBlockSize = (*currentBlockPtr)->getSize();
                int nextBlockSize = (*nextBlockPtr)->getSize();
                int newSize = currentBlockSize + nextBlockSize;

                /* Reset the data to null and request a new memory 
                chunk with the new size (this is  not necessary, 
                but it's better than having the both the memory 
                blocks' old data mixed together) */
                char data[newSize];
                for(int i = 0; i < newSize; ++i){
                    data[i] = '\0';
                }
                void* request = sbrk(newSize);
                strcpy((char*) request, data);

                /* Set the current block's new size and data*/
                (*currentBlockPtr)->setSize(newSize);
                (*currentBlockPtr)->isFree(true);
                (*currentBlockPtr)->setData((char*) request);
                (*currentBlockPtr)->setStartingAddress((char**) request);

                // Erase the next block
                freedMBList.erase(nextBlockPtr);

                // Reset the next block pointer
                nextBlockPtr = freedMBList.end();
            }
        } else {
            /* If current block is not free, move to the next block.*/
            currentBlockPtr = nextBlockPtr;
        }
    }
}

// Used to split a block
MemoryBlock* MemoryManager::splitBlock(list<MemoryBlock*>::iterator memoryBlockIter, int size){
    cout << "Splitting the block" << endl;
    list<MemoryBlock*>::iterator excessBlockPosition = memoryBlockIter;
    excessBlockPosition++;
    MemoryBlock* memoryBlock = (*memoryBlockIter);

    int excessBlockId = memoryBlock->getId() + 1000;
    int excessBlockSize = memoryBlock->getSize() - size;

    memoryBlock->setSize(size);

    MemoryBlock* excessBlock = new MemoryBlock();
    excessBlock->setId(excessBlockId);
    excessBlock->setSize(excessBlockSize);
    excessBlock->isFree(true);
    freedMBList.insert(excessBlockPosition, excessBlock);

    return memoryBlock;
}


