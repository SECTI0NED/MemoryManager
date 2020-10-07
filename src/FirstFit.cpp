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
    
    cout << "Alloc: " << endl;
    for(MemoryBlock* mb : allocMBList){
        cout << "Memory Block ID: " << mb->getId() << endl;
    }

    cout << "Freed: " << endl;
    for(MemoryBlock* mb : freedMBList){
        cout << "Memory Block ID: " << mb->getId() << endl;
    }

}

void FirstFit::allocateMemory(int numberOfBlocks) {
    if(numberOfBlocks <= dataList.size()){
        int id = 0;
        while(numberOfBlocks > 0){
            bool allocated = false;

            /* Get the data from the list of names
            and convert from string to cstring.*/
            string line = this->dataList.front();
            char cstring[line.size()];
            strcpy(cstring, line.c_str());
            const char* data = cstring;     // data in c-string
            int size = strlen(data);        // size of the data (No need for '+1')

            /* Use sbrk to allocate memory chunk 
            for the cstring in the Memory Block */
            void* request = sbrk(size);
            strcpy((char*) request, data);

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
                            break;

                        /* If the block has a larger size than needed, 
                        then split the block to get the required size*/
                        } else if(memoryBlock->getSize() > size) {
                            cout << "Found a memory block with a larger size." << endl;
                            MemoryBlock* splitMemoryBlock = splitBlock(mb, size);
                            splitMemoryBlock->isFree(false);
                            splitMemoryBlock->setData((char*) request);
                            splitMemoryBlock->setStartingAddress((char**) request);
                            allocated = true;
                            break;
                        }
                    }
                }
            /* If freedMBList is empty or the data has not been allocated ~
            yet, then create a new memory block and add it to allocMBList. */
            } else if(freedMBList.empty() || !allocated){
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
                allocated = true;
            }

            if(allocated){
                /* Reduce the size of the list and number of blocks */
                this->dataList.pop_front();
                numberOfBlocks-=1;
            }
        }
    } else {
        cout << "Error number of blocks requested: " << numberOfBlocks << endl
             << "Number of names in data list: " << dataList.size() << endl;
    }
    
}