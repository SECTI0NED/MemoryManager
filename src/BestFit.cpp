#include "../dep/BestFit.hpp"

BestFit::BestFit(string filename){
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

BestFit::~BestFit() {}

void BestFit::run(int allocateBlocks, int freeBlocks) {
    while(!dataList.empty()){
        allocateMemory(allocateBlocks);
        if(!dataList.empty()){
            freeMemory(freeBlocks);
            mergeBlocks();
        }
    }
    printDetails(BEST_FIT_FILENAME, BEST_FIT_LABEL);
    printDetailsConsole(BEST_FIT_FILENAME, BEST_FIT_LABEL);
}


list<MemoryBlock*>::iterator BestFit::retrieveBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator memoryBlockPtr = findBestFitBlock(sizeRequired, found);
    // if(*found == false){
    //    mergeBlocks();
    //    memoryBlockPtr = findBestFitBlock(sizeRequired, found);
    // }
    return memoryBlockPtr;
}

list<MemoryBlock*>::iterator BestFit::findBestFitBlock(int sizeRequired, bool* found) {
    bool firstSearch = true;
    list<MemoryBlock*>::iterator mb = freedMBList.begin();
    list<MemoryBlock*>::iterator memoryBlockPtr  = mb;
    for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        if((*mb)->isFree()){
            if((*mb)->getSize() >= sizeRequired) {
                if((*mb)->getSize() < (*memoryBlockPtr)->getSize()) {
                    memoryBlockPtr = mb;   
                    firstSearch = false;
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

