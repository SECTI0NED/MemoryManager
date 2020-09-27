/* 
    Class for representing Memoey
*/
#ifndef MEMORY_H
#define MEMORY_H

#include "./MemoryBlock.hpp"

class Memory {
    public:
        Memory();
        ~Memory();
        list<MemoryBlock*> allocMBList;
        list<MemoryBlock*> freedMBList;

};

#endif // MEMORY_H