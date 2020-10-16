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

/* Had to resort to changing the this->data to point to a different 
memory location or using sbrk to get a new chunk of memory, because changing 
the actual data resulted in segmentation faults.
This is because this->data is type 'char*' which is unmodifable.
For this->data be be overwritten, we have to change the type to 'char[SIZE]', 
but since we actually do not know the sizeupfront this is impossible to implement.
Sources:    
https://cboard.cprogramming.com/c-programming/153924-segmentation-fault-when-replacing-char-array.html
https://stackoverflow.com/questions/37164358/error-flexible-array-member-not-at-end-of-struct */
void MemoryBlock::resetData(const char* data){

    this->data = new char[size];
    strcpy(this->data, data);
    this->startingAddress = (char**) this->data;

    /* This is will cause segfaults: */
    // this->data = newData;
    // int counter = 0;
    // while(counter < size) {
    //     this->data[counter] = data[counter];
    //     counter++;
    // }
    // this->data[size] = '\0';
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

int* MemoryBlock::getDataStartingAddress() {
    return (int*) data;
}

bool MemoryBlock::isFree() {
    return blockIsFree;
}


MemoryBlock* MemoryBlock::getMemoryBlockAddress() {
    return this;
}


