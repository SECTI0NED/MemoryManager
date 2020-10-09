/*
    Class for representing a memory blcok
*/
#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include "./Utils.hpp"

class MemoryBlock {
    public:
        MemoryBlock();
        ~MemoryBlock();

        // Setters
        void setDataStartingAddress(memory_address getStartingAddress);
        void setData(char* data);
        void resetData(const char* data);
        void setSize(int size);
        void setId(int id);
        void isFree(bool blockIsFree);
        
        //Getters
        memory_address getDataStartingAddress();
        char* getData();
        int getSize();
        int getId();
        bool isFree();
        MemoryBlock* getMemoryBlockAddress();

        // Reset data to \0
        void clearData();


    private:
        memory_address startingAddress;
        char* data;
        int size;
        int id;
        bool blockIsFree;
};

#endif // MEMORY_BLOCK_H