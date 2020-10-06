#include "../dep/FirstFit.hpp"

FirstFit::FirstFit(list<char*>* data) {
    for(char_ptr_iterator i = data->begin(); i != data->end(); ++i){
        this->data.push_back(*i);
    }
}

FirstFit::~FirstFit() {}

void FirstFit::run(int allocateBlocks, int freeBlocks) {
    allocateMemory(allocateBlocks);
    // while(!data.empty()){
    //     allocateMemory(allocateBlocks);
    //     freeMemory(freeBlocks);
    // }
    // for(list<MemoryBlock*>::iterator i = allocMBList.begin(); i != allocMBList.end(); ++i){
    //     cout << "Memory Block ID: " << (*i)->getId() << endl;
    // }
    // for(list<MemoryBlock*>::iterator i = freedMBList.begin(); i != freedMBList.end(); ++i){
    //     cout << "Memory Block ID: " << (*i)->getId() << endl;
    // }
}

void FirstFit::allocateMemory(int blocks) {
    int counter = 0;
    int numberOfBlocks = blocks;
    
    while(numberOfBlocks > 0){
        //cout << numberOfBlocks << endl;
        /* Get the data from the list of names */
        const char* data = "FUCK";

        /* Create Memory Block */
        MemoryBlock* memoryBlock = (MemoryBlock*)malloc(sizeof(MemoryBlock*));
        int size = strlen(data) + 1;
        void* request = sbrk(size);
        strcpy((char*) request, data);
        memoryBlock->setId(counter);
        memoryBlock->setSize(size);
        memoryBlock->setData((char*) request);
        memoryBlock->setStartingAddress((char**) request);
        ++counter;

        /* Reduce the size of the list and number of blocks */
        //this->data.pop_front();
        numberOfBlocks = numberOfBlocks - 1;
        cout << "Completed" << endl;

        // /* Decide where to allocate the block (allocMBList or freedMBList) */
        // if(freedMBList.empty()){
        //     allocMBList.push_back(memoryBlock);
        // } else {
        //     // Go through each block of freedMBList to select a MemoryBlock
        //     // If MB already occupied or does not have enough space
        //     // Then allocate the block to allocMBList.
        // }
        
    }
}