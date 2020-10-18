/*
    Class for representing a memory block
*/
#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include "./Utils.hpp"

class MemoryBlock {
    public:
        MemoryBlock();
        ~MemoryBlock();

        // Setters
        void setData(char* data);
        void resetData(const char* data);
        void setSize(int size);
        void isFree(bool blockIsFree);
        
        //Getters
        int* getDataStartingAddress();
        char* getData();
        int getSize();
        bool isFree();
        MemoryBlock* getMemoryBlockAddress();

        // For debugging
        void setId(int id);
        int getId();
        
    private:
        char* data;
        int size;
        int id;
        bool blockIsFree;
};

#endif // MEMORY_BLOCK_H