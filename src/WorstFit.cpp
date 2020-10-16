#include "../dep/WorstFit.hpp"

WorstFit::WorstFit(string filename){
    dataSourceFile = filename;
    ifstream stream(filename);
    string line = "";
    while(!stream.eof()){
        stream >> line; 
        dataList.push_back(line);
    }
    stream.close();
}

WorstFit::~WorstFit() {}

void WorstFit::run(int allocateBlocks, int freeBlocks) {
    while(!dataList.empty()){
        // Allocate number of 'allocateBlocks'
        allocateMemory(allocateBlocks);
        if(!dataList.empty()){
            // Randomly free number of 'freeBlocks'
            freeMemory(freeBlocks);
            mergeBlocks();
        }
    }
    printDetails(WORST_FIT_FILENAME, WORST_FIT_LABEL);
    printDetailsConsole(WORST_FIT_FILENAME, WORST_FIT_LABEL);
}
// Returns the block found by the worst fit algorithm
list<MemoryBlock*>::iterator WorstFit::retrieveBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator memoryBlockPtr = findWorstFitBlock(sizeRequired, found);
    return memoryBlockPtr;
}

list<MemoryBlock*>::iterator WorstFit::findWorstFitBlock(int sizeRequired, bool* found) {
    /* To prevent the desired block from resetting 'firstSearch' 
    indicates whether the algorithm is on its first search and 
    has not found a block smaller than the first block in freedMBList. */
    bool firstSearch = true;

    // MemoryBlock pointer to the first node in freedMBList.
    list<MemoryBlock*>::iterator mb = freedMBList.begin();

    // MemoryBlock pointer holding the desired block.
    list<MemoryBlock*>::iterator memoryBlockPtr  = mb;

    // Begin searching...
    for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        // Checks if block is free
        if((*mb)->isFree()){
            // Checks if the current block size is large enough for the data size
            if((*mb)->getSize() >= sizeRequired) {
                /* Checks if the current block size is less that 
                the desired block to return. */
                if((*mb)->getSize() > (*memoryBlockPtr)->getSize()) {
                    memoryBlockPtr = mb;    
                    firstSearch = false;
                /* Checks if a desired block is smaller than the first block in freedMBlist*/
                } else if(firstSearch){
                    memoryBlockPtr = mb; 
                    firstSearch = false;
                }
                *found = true;
            } 
        }
    }
    return memoryBlockPtr;
}