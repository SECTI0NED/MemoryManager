
/* 
    For testing
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "../dep/MemoryManager.hpp"

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    MemoryManager* memory = new MemoryManager();

    MemoryBlock* memoryBlock1 = (MemoryBlock*)malloc(sizeof(MemoryBlock*));
    const char* data1 = "Nikita";
    int size1 = strlen(data1) + 1;
    void* request1 = sbrk(size1);
    strcpy((char*) request1, data1);
    memoryBlock1->setData((char*) request1);
    memoryBlock1->setStartingAddress((char**) request1);
    memoryBlock1->setSize(size1);

    MemoryBlock* memoryBlock2 = (MemoryBlock*)malloc(sizeof(MemoryBlock*));
    const char* data2 = "Hugh";
    int size2 = strlen(data2) + 1;
    void* request2 = sbrk(size2);
    strcpy((char*) request2, data2);
    memoryBlock2->setData((char*) request2);
    memoryBlock2->setStartingAddress((char**) request2);
    memoryBlock2->setSize(size2);

    MemoryBlock* memoryBlock3 = (MemoryBlock*)malloc(sizeof(MemoryBlock*));
    const char* data3 = "Martin";
    int size3 = strlen(data3) + 1;
    void* request3 = sbrk(size3);
    strcpy((char*) request3, data3);
    memoryBlock3->setData((char*) request3);
    memoryBlock3->setStartingAddress((char**) request3);
    memoryBlock3->setSize(size3);

    MemoryBlock* memoryBlock4 = (MemoryBlock*)malloc(sizeof(MemoryBlock*));
    const char* data4 = "Dylan";
    int size4 = strlen(data4) + 1;
    void* request4 = sbrk(size4);
    strcpy((char*) request4, data4);
    memoryBlock4->setData((char*) request4);
    memoryBlock4->setStartingAddress((char**) request4);
    memoryBlock4->setSize(size4);

    memory->test.push_back(memoryBlock1);
    memory->test.push_back(memoryBlock2);
    memory->test.push_back(memoryBlock3); 
    memory->test.push_back(memoryBlock4);

    for(MemoryBlock* mb: memory->test){
        cout << "Memory Block details:" << endl;
        cout << "Starting address: " << mb->getStartingAddress() << endl;
        cout << "Data: " << mb->getData() << endl;
        cout << "Size: " << mb->getSize() << endl;
    }
    
    return 0;
}
