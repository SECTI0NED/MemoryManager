#include "../dep/MemoryManager.hpp"

MemoryManager::MemoryManager() {}
MemoryManager::MemoryManager(list<char*>* data) {}

MemoryManager::~MemoryManager() {}

void MemoryManager::allocateMemory(int blocks) {
    // Each Memory Manager will have its own implementation of allocateMemory().
}

void MemoryManager::freeMemory(int blocks) {

}

void MemoryManager::mergeBlocks() {

}

void run(int allocate, int free) {

}

