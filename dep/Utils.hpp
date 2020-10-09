
#ifndef UTILS_H
#define UTILS_H


/***************************************INCLUDES****************************************/
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <list>
#include <string>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
using std::string;
using std::list;
using std::cin;
using std::ifstream;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::ofstream;

/***************************************DEFINES****************************************/

#define FIRST_FIT "ff"
#define BEST_FIT "bf"
#define WORST_FIT "wf"

#define ALLOCATE 1000
#define FREE 500

#define FIRST_FIT_FILENAME "_firstfit.txt"
#define BEST_FIT_FILENAME "_bestfit.txt"
#define WORST_FIT_FILENAME "_worstfit.txt"

#define FIRST_FIT_LABEL "FIRST FIT"
#define BEST_FIT_LABEL "BEST FIT"
#define WORST_FIT_LABEL "WORST FIT"

#define SBRK_TOTAL "[TOTAL MEMORY ALLOCATED BY SBRK]:"
#define FREED_INFO "[FREED MEMORY BLOCK LIST]"
#define ALLOC_INFO "[ALLOCATED MEMORY BLOCK LIST]"
#define MEMORY_BLOCK_ADDRESS "[MEMORY BLOCK ADDRESS]:"
#define MEMORY_BLOCK_SIZE "[SIZE]:"
#define MEMORY_BLOCK_CONTENTS "[CONTENTS]:"
#define CONTENTS_STARTING_ADDRESS "[CONTENTS STARTING ADDRESS]:"

/***************************************TYPEDEFS**************************************/

typedef char** memory_address;
typedef list<char*>::iterator char_ptr_iterator;

#endif // UTILS_H