#include "../dep/FirstFit.hpp"

FirstFit::FirstFit(string filename) {
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
        freeMemory(freeBlocks);
    }
    // for(list<MemoryBlock*>::iterator i = allocMBList.begin(); i != allocMBList.end(); ++i){
    //     cout << "Memory Block ID: " << (*i)->getId() << endl;
    // }
    // for(list<MemoryBlock*>::iterator i = freedMBList.begin(); i != freedMBList.end(); ++i){
    //     cout << "Memory Block ID: " << (*i)->getId() << endl;
    // }
}

void FirstFit::allocateMemory(int numberOfBlocks) {

    int counter = 0;
    while(counter != numberOfBlocks){
        cout << counter << endl;
        /* Create Memory Block */
        MemoryBlock* memoryBlock = new MemoryBlock();     
        /* Get the data from the list of names
        and convert from string to cstring.*/
        string line = this->dataList.front();
        char cstring[line.size()];
        strcpy(cstring, line.c_str());

        const char* data = cstring;
        int size = strlen(data) + 1;
        void* request = sbrk(size);
        strcpy((char*) request, data);
        memoryBlock->setId(counter);
        memoryBlock->setSize(size);
        memoryBlock->setData((char*) request);
        memoryBlock->setStartingAddress((char**) request);
        ++counter;

        /* Reduce the size of the list and number of blocks */
        this->dataList.pop_front();

        /* Decide where to allocate the block (allocMBList or freedMBList) */
        if(freedMBList.empty()){
            allocMBList.push_back(memoryBlock);
        } else {
            // Go through each block of freedMBList to select a MemoryBlock
            // If MB already occupied or does not have enough space
            // Then allocate the block to allocMBList.
        }
        
    }
}