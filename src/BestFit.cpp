#include "../dep/BestFit.hpp"

BestFit::BestFit(string filename){
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
        }
    }
}

void BestFit::allocateMemory(int numberOfRequestedBlocks) {
    int sbrkTotal = 0;
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
            /* 
                Go through entire list and find the SMAILLEST block that can store the data. 
                If Block is NOT null then assign data (if block is null, then that means no satisfiable block was found)
                Set allocated = true
            */
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

    
    printDetails(BEST_FIT_FILENAME, BEST_FIT_LABEL, sbrkTotal);
}