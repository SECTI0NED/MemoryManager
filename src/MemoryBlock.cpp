#include "../dep/MemoryBlock.hpp"

MemoryBlock::MemoryBlock() {}

MemoryBlock::~MemoryBlock() {}

void MemoryBlock::setId(int id){
    this->id = id;
}

void MemoryBlock::setSize(int size) {
    this->size = size;
}

void MemoryBlock::setData(char* data) {
    this->data = data;
}

/* Had to resort to using sbrk here, changing 
the actual data resulted in segfaults */
void MemoryBlock::resetData(const char* data){
    void* request = sbrk(size);
    strcpy((char*) request, data);
    this->data = (char*) request;
    this->startingAddress = (char**) request;

    // int counter = 0;
    // while(counter < size) {
    //     this->data[counter] = data[counter];
    //     counter++;
    // }
    // this->data[size] = '\0';
}

void MemoryBlock::setDataStartingAddress(memory_address startingAddress) {
    this->startingAddress = startingAddress;
}

void MemoryBlock::isFree(bool blockIsFree){
    this->blockIsFree = blockIsFree;
}

int MemoryBlock::getId() {
    return id;
}

int MemoryBlock::getSize(){
    return size;
}

char* MemoryBlock::getData() {
    return data;
}

memory_address MemoryBlock::getDataStartingAddress() {
    return startingAddress;
}

bool MemoryBlock::isFree() {
    return blockIsFree;
}

void MemoryBlock::clearData() {
    int counter = 0;
    while(counter <= size){
        data[counter] = '\0';
        counter++;
    }
    blockIsFree = true;
}

MemoryBlock* MemoryBlock::getMemoryBlockAddress() {
    return this;
}


