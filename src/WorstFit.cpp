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
        allocateMemory(allocateBlocks);
        if(!dataList.empty()){
            freeMemory(freeBlocks);
        }
    }
    printDetails(WORST_FIT_FILENAME, WORST_FIT_LABEL);
    printDetailsConsole(WORST_FIT_FILENAME, WORST_FIT_LABEL);
}

list<MemoryBlock*>::iterator WorstFit::retrieveBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator memoryBlockPtr = findWorstFitBlock(sizeRequired, found);
    if(*found == false){
       mergeBlocks();
       memoryBlockPtr = findWorstFitBlock(sizeRequired, found);
    }
    return memoryBlockPtr;
}

list<MemoryBlock*>::iterator WorstFit::findWorstFitBlock(int sizeRequired, bool* found) {
    bool firstSearch = true;
    list<MemoryBlock*>::iterator mb = freedMBList.begin();
    list<MemoryBlock*>::iterator memoryBlockPtr  = mb;
    for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        if((*mb)->isFree()){
            if((*mb)->getSize() >= sizeRequired) {
                if((*mb)->getSize() > (*memoryBlockPtr)->getSize()) {
                    memoryBlockPtr = mb;    
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