#include "../dep/MemoryBlock.hpp"

MemoryBlock::MemoryBlock() {}

MemoryBlock::~MemoryBlock() {}

void MemoryBlock::setStartingAddress(memory_address startingAddress) {
    this->startingAddress = startingAddress;
}

void MemoryBlock::setData(char* data) {
    this->blockIsfree = false;
    this->data = data;
}

void MemoryBlock::setSize(int size) {
    this->size = size;
}

void MemoryBlock::setId(int id){
    this->id = id;
}

memory_address MemoryBlock::getStartingAddress() {
    return startingAddress;
}

char* MemoryBlock::getData() {
    return data;
}

int MemoryBlock::getSize(){
    return size;
}

int MemoryBlock::getId() {
    return id;
}

void MemoryBlock::clearData() {
    int counter = 0;
    while(data[counter] != '\0'){
        data[counter] = '\0';
        counter++;
    }
    blockIsfree = true;
}

bool MemoryBlock::isFree() {
    return blockIsfree;
}

