#include "../dep/MemoryBlock.hpp"

MemoryBlock::MemoryBlock() {}

MemoryBlock::~MemoryBlock() {}

void MemoryBlock::setStartingAddress(memory_address startingAddress) {
    this->startingAddress = startingAddress;
}

void MemoryBlock::setData(char* data) {
    this->data = data;
}

void MemoryBlock::setSize(int size) {
    this->size = size;
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