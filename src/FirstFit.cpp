#include "../dep/FirstFit.hpp"

FirstFit::FirstFit(string filename) {
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

FirstFit::~FirstFit() {}

void FirstFit::run(int allocateBlocks, int freeBlocks) {
    while(!dataList.empty()){
        allocateMemory(allocateBlocks);
        if(!dataList.empty()){
            freeMemory(freeBlocks);
            mergeBlocks();
        }
    }
    printDetails(FIRST_FIT_FILENAME, FIRST_FIT_LABEL);
    printDetailsConsole(FIRST_FIT_FILENAME, FIRST_FIT_LABEL);
}


// Returns the block found by the first fit algorithm
list<MemoryBlock*>::iterator FirstFit::retrieveBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator memoryBlockPtr = findFirstFitBlock(sizeRequired, found);
    return memoryBlockPtr;
}

list<MemoryBlock*>::iterator FirstFit::findFirstFitBlock(int sizeRequired, bool* found) {
    // MemoryBlock pointer to the first node in freedMBList
    list<MemoryBlock*>::iterator mb = freedMBList.begin();
    
    // MemoryBlock pointer holding the desired block.
    list<MemoryBlock*>::iterator memoryBlockPtr  = mb;

    // Begin searching...
    for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        // Checks if block is free
        if((*mb)->isFree()){
            // Checks if the current block size is large enough for the data size
            if((*mb)->getSize() >= sizeRequired) {
                /* If requirements are satisfied return the block and halt the loop. */
                memoryBlockPtr = mb;
                *found = true;
                break;
            } 
        }
    }
    return memoryBlockPtr;
}