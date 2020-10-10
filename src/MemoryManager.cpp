#include "../dep/MemoryManager.hpp"
#include <random>

MemoryManager::MemoryManager() {}
MemoryManager::~MemoryManager() {}


MemoryManager::MemoryManager(string filename) {
    sbrkTotal = 0;
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

/* Need to select random block from allocMBList */
void MemoryManager::freeMemory(int numberOfRequestedBlocks) {
    int numberOfBlocks = 0;
    if(numberOfRequestedBlocks  <= (int) allocMBList.size()){
        numberOfBlocks = numberOfRequestedBlocks;
    } else {
        numberOfBlocks = allocMBList.size();
    }

    while(numberOfBlocks > 0){
    
        /* Get random positon in allocMBList */
        list<MemoryBlock*>::iterator randomPosition = allocMBList.begin();
        int random = rand() % allocMBList.size();
        std::advance(randomPosition, random);
        
        /* Get a random memory block from allocMBList */
        MemoryBlock* memoryBlock = (*randomPosition);
    
        memoryBlock->isFree(true);

        /* Add this block to the freedMBList*/
        freedMBList.push_back(memoryBlock);

        /* Remove the block from the allocMBList 
        and reduce the amount of blocks to free*/
        allocMBList.erase(randomPosition);
        numberOfBlocks-=1;
    } 
}


/* For merging consecutive free blocks in freedMBList */
void MemoryManager::mergeBlocks() {

    list<MemoryBlock*>::iterator currentBlockPtr = freedMBList.begin();
    list<MemoryBlock*>::iterator nextBlockPtr = freedMBList.end();

    while((*currentBlockPtr) != freedMBList.back()){
        nextBlockPtr = currentBlockPtr;
        nextBlockPtr++;
        if((*currentBlockPtr)->isFree() && (*nextBlockPtr)->isFree()){
            /* Retrieve the new size of the memory block */
            int currentBlockSize = (*currentBlockPtr)->getSize();
            int nextBlockSize = (*nextBlockPtr)->getSize();
            int newSize = currentBlockSize + nextBlockSize;
            
            /* Set the current block's new size */
            (*currentBlockPtr)->setSize(newSize);
            (*currentBlockPtr)->isFree(true);

            /* Erase the next block */
            freedMBList.erase(nextBlockPtr);

            /* Reset the next block pointer */
            nextBlockPtr = freedMBList.end();
  
            mergeTotal++;
           
        } else {
            /* If current and next block is not free, 
            move current block pointer to the next one.*/
            currentBlockPtr = nextBlockPtr;
        }
    }
}

/* Used to split a block */
MemoryBlock* MemoryManager::splitBlock(list<MemoryBlock*>::iterator memoryBlockIter, int size){
    splitTotal++;
    /* Get position of excess memory block */
    list<MemoryBlock*>::iterator excessBlockPosition = memoryBlockIter;
    excessBlockPosition++;
    
    /* Current memory block = memoryBlock */
    MemoryBlock* memoryBlock = (*memoryBlockIter);

    /* Get excess block details */
    int excessBlockId = memoryBlock->getId() + 1000;
    int excessBlockSize = memoryBlock->getSize() - size;

    /* Set the size needed for the current memory block */
    memoryBlock->setSize(size);

    /* Create the excess block with the excess size */
    MemoryBlock* excessBlock = new MemoryBlock();
    excessBlock->setId(excessBlockId);
    excessBlock->setSize(excessBlockSize);
    excessBlock->isFree(true);
    freedMBList.insert(excessBlockPosition, excessBlock);

    /* Return the block with the required amount of space */
    return memoryBlock;
}

/* For printing details */
void MemoryManager::printDetails(string filename, string managerTypeLabel){
    ofstream fileStream(filename);
    fileStream << managerTypeLabel << endl
    << "[NO. OF TIMES BLOCKS WERE SPLIT]: " << splitTotal << endl
    << "[NO. OF TIMES BLOCKS WERE MERGED]: " << mergeTotal << endl
    << SBRK_TOTAL << "\t" << sbrkTotal << endl
    << LINE_BREAK << endl
    << FREED_INFO << " - Size: " << freedMBList.size() << endl;
    for(list<MemoryBlock*>::iterator mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        fileStream << MEMORY_BLOCK_ADDRESS << '\t' 
        << (*mb)->getMemoryBlockAddress()
        << "\t\t" << MEMORY_BLOCK_SIZE << '\t'
        << (*mb)->getSize();
        if(!(*mb)->isFree()) {
            fileStream << "\t\t"
            << CONTENTS_STARTING_ADDRESS << ' '
            << (*mb)->getDataStartingAddress();
            fileStream << "\t\t"
            << MEMORY_BLOCK_CONTENTS << '\t';
            for(int i = 0; (*mb)->getData()[i] != '\0'; ++i){
                fileStream << (*mb)->getData()[i];
            }
            fileStream << endl;
        } else {
            fileStream << endl;
        }
    }
    fileStream << endl;
    fileStream << ALLOC_INFO << " - Size: " << allocMBList.size() << endl;
    for(list<MemoryBlock*>::iterator mb = allocMBList.begin(); mb != allocMBList.end(); ++mb) {
        fileStream << MEMORY_BLOCK_ADDRESS << '\t'
        << (*mb)->getMemoryBlockAddress() 
        << "\t\t" << MEMORY_BLOCK_SIZE << '\t'
        << (*mb)->getSize();
        fileStream << "\t\t" 
        << CONTENTS_STARTING_ADDRESS << ' '
        << (*mb)->getDataStartingAddress()
        << "\t\t" << MEMORY_BLOCK_CONTENTS << '\t';
        for(int i = 0; (*mb)->getData()[i] != '\0'; ++i){
            fileStream << (*mb)->getData()[i];
        }
        fileStream << endl;
    }
    fileStream.close();
}


