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
}

void FirstFit::allocateMemory(int numberOfRequestedBlocks) {
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

        /* Use sbrk to allocate memory chunk 
        for the cstring in the Memory Block */
        void* request = sbrk(size);
        sbrkTotal+=size;
        strcpy((char*) request, data);
        
        /* Decide where to allocate the information (allocMBList or freedMBList) */
        if(!freedMBList.empty()){
            list<MemoryBlock*>::iterator mb;
            for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb) {
                MemoryBlock* memoryBlock = (*mb);
                if(memoryBlock->isFree()) {
                    /* If the block is the same size needed, 
                    then allocate the data to this block */
                    if(memoryBlock->getSize() == size) {
                        memoryBlock->isFree(false);
                        memoryBlock->setData((char*) request);
                        memoryBlock->setDataStartingAddress((char**) request);
                        allocated = true;
                        break;

                    /* If the block has a larger size than needed, 
                    then split the block to get the required size*/
                    } else if(memoryBlock->getSize() > size) {
                        MemoryBlock* splitMemoryBlock = splitBlock(mb, size);
                        splitMemoryBlock->isFree(false);
                        splitMemoryBlock->setData((char*) request);
                        splitMemoryBlock->setDataStartingAddress((char**) request);
                        mergeBlocks();
                        allocated = true;
                        break;
                    }
                }
            }
        }

        /* If freedMBList is empty or the data has not been allocated 
        yet, then create a new memory block and add it to allocMBList. */
        if(freedMBList.empty() || !allocated){
            MemoryBlock* memoryBlock = new MemoryBlock();  
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

    printDetails(FIRST_FIT_FILENAME, FIRST_FIT_LABEL, sbrkTotal);
   
}