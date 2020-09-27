/*
    Class for representing a memory blcok
*/
#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include "./Types.hpp"

class MemoryBlock {
    public:
        MemoryBlock();
        ~MemoryBlock();

        // Setters
        void setStartingAddress(memory_address getStartingAddress);
        void setData(char* data);
        void setSize(int size);
        
        //Getters
        memory_address getStartingAddress();
        char* getData();
        int getSize();

        
    private:
        memory_address startingAddress;
        char* data;
        int size;

};

#endif // MEMORY_BLOCK_H