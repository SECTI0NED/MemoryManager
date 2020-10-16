#include "../dep/MemoryManager.hpp"
#include <random>

MemoryManager::MemoryManager() {}
MemoryManager::~MemoryManager() {}


MemoryManager::MemoryManager(string filename) {
    dataSourceFile = filename;
    sbrkTotal = 0;
    ifstream stream(filename);
    string line = "";
    while(!stream.eof()){
        stream >> line; 
        dataList.push_back(line); 
    }
    stream.close();
}

// Each Memory Manager will have its own implementation of run().
void MemoryManager::run(int allocate, int free) {}

 // Each Memory Manager will have its own implementation of retreiveBlock().
list<MemoryBlock*>::iterator MemoryManager::retrieveBlock(int sizeRequired, bool* found) {
     *found = false;
     return freedMBList.begin();
}

void MemoryManager::allocateMemory(int numberOfRequestedBlocks) {
    // Set the numberOfBlocks to allocate
   int numberOfBlocks = 0;
    if(numberOfRequestedBlocks <= (int) dataList.size()){
        numberOfBlocks = numberOfRequestedBlocks;
    } else {
        numberOfBlocks = dataList.size();
    }
    
    int id = 1;
    while(numberOfBlocks > 0){
        bool allocated = false;
        /* Get the data from the list of names
        and convert from string to cstring.*/
        string line = this->dataList.front();
        char cstring[line.size()];
        strcpy(cstring, line.c_str());
        
        const char* data = cstring;         // data in c-string
        int size = strlen(data) + 1;        // size of the data
        
        /* Decide where to allocate the information (allocMBList or freedMBList) */
        if(!freedMBList.empty()){
            /* If there are memory blocks in the freedMBList then 
            search to find it to a block to allocate the data. */
            bool found = false;

            /* retreiveBlock() uses the child classes' method of 
            retrieveBlock to get the block according to its type of alogorthm */
            list<MemoryBlock*>::iterator memoryBlockPtr = retrieveBlock(size, &found);

            // If a block was found then allocate data accordingly
            if(found){
                /* If the block size is the exact same as the size 
                of the data then don't split the block, otherwise 
                split and merge the block */
                MemoryBlock* memoryBlock = *memoryBlockPtr;
                if(memoryBlock->getSize() == size){
                    memoryBlock->isFree(false);
                    memoryBlock->resetData(data);
                    allocated = true;
                } else if(memoryBlock->getSize() > size){
                    MemoryBlock* splitMemoryBlock = splitBlock(memoryBlockPtr, size);
                    splitMemoryBlock->isFree(false);
                    splitMemoryBlock->resetData(data);
                    mergeBlocks();
                    allocated = true;
                }
            }
        }

        /* If freedMBList is empty or the data has not been allocated 
        yet, then create a new memory block and add it to allocMBList. */
        if(freedMBList.empty() || !allocated){
            MemoryBlock* memoryBlock = new MemoryBlock(); 
            
            /* Use sbrk to allocate memory chunk 
            for the cstring in the Memory Block */
            void* request = sbrk(size);
            sbrkTotal+=size;
            strcpy((char*) request, data);

            memoryBlock->setId(id);
            memoryBlock->setSize(size);
            memoryBlock->isFree(false);
            memoryBlock->setData((char*) request);
            ++id;
            allocMBList.push_back(memoryBlock);
            allocated = true;
        }

        if(allocated){
            /* Reduce the size of the list and number of blocks */
            this->dataList.pop_front();
            numberOfBlocks-=1;
        }
    }
}

/* For 'freeing' memory (moving a block from allocMBList to freedMBList) */
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

// Utility method for merging blocks
bool compareAddress(MemoryBlock* first, MemoryBlock* second) {
    return (first->getDataStartingAddress() < second->getDataStartingAddress());
}

// Utility method for merging blocks
bool MemoryManager::adjacentInMemory(MemoryBlock* first, MemoryBlock* second){
    bool equal = false;
    char* endAddressOfFirst = first->getData() + first->getSize();

    if((int*) endAddressOfFirst == second->getDataStartingAddress()){
        equal = true;
    }
    return equal;
}

/* For merging adjacent free blocks in memory */
void MemoryManager::mergeBlocks() {
    // Sort by memory of the data
    freedMBList.sort(compareAddress);
    list<MemoryBlock*>::iterator currentBlockPtr = freedMBList.begin();
    list<MemoryBlock*>::iterator nextBlockPtr = freedMBList.end();

    while((*currentBlockPtr) != freedMBList.back()){
        nextBlockPtr = currentBlockPtr;
        nextBlockPtr++;
        if((*currentBlockPtr)->isFree() && (*nextBlockPtr)->isFree() 
            && adjacentInMemory((*currentBlockPtr), (*nextBlockPtr))) {
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

/* For printing details to file*/
void MemoryManager::printDetails(string filename, string managerTypeLabel){
    ofstream fileStream(filename);
    fileStream << DATA_SOURCE_FILE << "\t\t\t" << dataSourceFile << endl
    << TITLE << "\t\t\t" << managerTypeLabel << endl
    << SBRK_TOTAL << "\t\t" << sbrkTotal << " bytes" << endl
    << FREED_SIZE << "\t\t\t" << freedMBList.size() << endl
    << ALLOC_SIZE << "\t\t\t" << allocMBList.size() << endl
    << SPLIT << "\t\t" << splitTotal << endl
    << MERGED << "\t\t" <<  mergeTotal << endl
    << endl
    << LINE_BREAK << endl;
    fileStream << FREED_TITLE << endl;
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
    fileStream << endl << LINE_BREAK << endl;
    fileStream << ALLOC_TITLE << endl;
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

/* For printing details to console */
void MemoryManager::printDetailsConsole(string filename, string managerTypeLabel){
    cout << LINE_BREAK_SHORT << endl;
    cout << TITLE << "\t\t\t" << managerTypeLabel << endl
         << SBRK_TOTAL << "\t\t" << sbrkTotal << " bytes" << endl
         << FREED_SIZE << "\t\t\t" << freedMBList.size() << endl
         << ALLOC_SIZE << "\t\t\t" << allocMBList.size() << endl
         << SPLIT << "\t\t" << splitTotal << endl
         << MERGED << "\t\t" <<  mergeTotal << endl
         << endl
         << "See '" << filename << "' for more details." << endl
         << endl;
    cout << LINE_BREAK_SHORT << endl;
}
