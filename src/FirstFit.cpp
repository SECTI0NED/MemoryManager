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
        cout << "--Allocating data--" << endl;
        allocateMemory(allocateBlocks);

        if(!dataList.empty()){
            cout << "--Freeing memory blocks--"<< endl;
            freeMemory(freeBlocks);
        }
        
    }
    cout << "**********************************" << endl;
    cout << "Alloc: " << endl;
    for(MemoryBlock* mb : allocMBList){
        cout << "Memory Block ID: " << mb->getId() << endl;
        cout << "Memory Block Data: " << endl;
        for(int i = 0; mb->getData()[i] != '\0'; ++i){
            cout << mb->getData()[i];
        }
        cout << endl;
    }
    cout << "Freed: " << endl;
    for(MemoryBlock* mb : freedMBList){
        cout << "Memory Block ID: " << mb->getId() << endl;
        if(!mb->isFree()){
            cout << "Memory Block Data: " << endl;
            for(int i = 0; mb->getData()[i] != '\0'; ++i){
                cout << mb->getData()[i];
            }
            cout << endl;
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
    
    int id = 0;
    while(numberOfBlocks > 0){
        bool allocated = false;

        /* Get the data from the list of names
        and convert from string to cstring.*/
        string line = this->dataList.front();
        char cstring[line.size()];
        strcpy(cstring, line.c_str());
        const char* data = cstring;     // data in c-string
        int size = strlen(data) + 1;        // size of the data

        /* Use sbrk to allocate memory chunk 
        for the cstring in the Memory Block */
        void* request = sbrk(size);
        strcpy((char*) request, data);
        cout << "Size required: " << size << endl;
        
        /* Decide where to allocate the information (allocMBList or freedMBList) */
        if(!freedMBList.empty()){
            cout << "freedMBList is NOT empty." << endl;
            list<MemoryBlock*>::iterator mb;
            for(mb = freedMBList.begin(); mb != freedMBList.end(); ++mb) {
                MemoryBlock* memoryBlock = (*mb);
                if(memoryBlock->isFree()) {
                    /* If the block is the same size needed, 
                    then allocate the data to this block */
                    if(memoryBlock->getSize() == size) {
                        cout << "Found a memory block with exact size required." << endl;
                        memoryBlock->isFree(false);
                        memoryBlock->setData((char*) request);
                        memoryBlock->setStartingAddress((char**) request);
                        allocated = true;
                        cout << "Allocated" << endl;
                        break;

                    /* If the block has a larger size than needed, 
                    then split the block to get the required size*/
                    } else if(memoryBlock->getSize() > size) {
                        cout << "Found a memory block with a larger size: " << memoryBlock->getSize() << endl;
                        MemoryBlock* splitMemoryBlock = splitBlock(mb, size);
                        splitMemoryBlock->isFree(false);
                        splitMemoryBlock->setData((char*) request);
                        splitMemoryBlock->setStartingAddress((char**) request);
                        
                        /* merge the excess block if it 
                        adjacent to a cleared block */
                        mergeBlocks();

                        allocated = true;
                        cout << "Allocated" << endl;
                        break;
                    }
                }
            }
        }
        /* If freedMBList is empty or the data has not been allocated ~
        yet, then create a new memory block and add it to allocMBList. */
        if(freedMBList.empty() || !allocated){
            cout << "freedMBList is empty or data not allocated" << endl;
            /* Create Memory Block */
            MemoryBlock* memoryBlock = new MemoryBlock();  

            /* Set info for the Memory Block */
            memoryBlock->setId(id);
            memoryBlock->setSize(size);
            memoryBlock->isFree(false);
            memoryBlock->setData((char*) request);
            memoryBlock->setStartingAddress((char**) request);
            ++id;
            allocMBList.push_back(memoryBlock);
            cout << "Allocated" << endl;
            allocated = true;
        }

        if(allocated){
            /* Reduce the size of the list and number of blocks */
            this->dataList.pop_front();
            numberOfBlocks-=1;
        }
    }

        
    
    
}