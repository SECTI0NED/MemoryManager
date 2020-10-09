#include "../dep/WorstFit.hpp"

WorstFit::WorstFit(string filename){

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
}

void WorstFit::allocateMemory(int numberOfRequestedBlocks) {
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
      
            bool found = false;
            list<MemoryBlock*>::iterator memoryBlockPtr = findWorstFitBlock(size, &found);
            if(found){
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
            memoryBlock->setDataStartingAddress((char**) request);
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
list<MemoryBlock*>::iterator WorstFit::findWorstFitBlock(int sizeRequired, bool* found) {
    list<MemoryBlock*>::iterator mb = freedMBList.begin();
    list<MemoryBlock*>::iterator memoryBlockPtr  = mb;
    for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb){
        if((*mb)->isFree()){
            if(sizeRequired <= (*mb)->getSize()) {
                memoryBlockPtr = mb;
                *found = true;
                if((*mb)->getSize() >= (*memoryBlockPtr)->getSize()) {
                    memoryBlockPtr = mb;
                    *found = true;
                }
            } 
        }
    }
    return memoryBlockPtr;
}