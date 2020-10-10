#include "../dep/FirstFit.hpp"

FirstFit::FirstFit(string filename) {
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
        }
    }
    printDetails(FIRST_FIT_FILENAME, FIRST_FIT_LABEL);
}

list<MemoryBlock*>::iterator FirstFit::retrieveBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator memoryBlockPtr = findFirstFitBlock(sizeRequired, found);
    if(*found == false){
       mergeBlocks();
       memoryBlockPtr = findFirstFitBlock(sizeRequired, found);
    }
    return memoryBlockPtr;
}

list<MemoryBlock*>::iterator FirstFit::findFirstFitBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator mb = freedMBList.begin();
    list<MemoryBlock*>::iterator memoryBlockPtr  = mb;
    for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        if((*mb)->isFree()){
            if((*mb)->getSize() >= sizeRequired) {
                memoryBlockPtr = mb;
                *found = true;
                break;
            } 
        }
    }
    return memoryBlockPtr;
}