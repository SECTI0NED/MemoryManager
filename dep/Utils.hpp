
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


#define FIRST_FIT_LABEL "First Fit"
#define BEST_FIT_LABEL "Best Fit"
#define WORST_FIT_LABEL "Worst Fit"

#define FREED_TITLE "freedMBList:"
#define ALLOC_TITLE "allocMBList:"

#define TITLE "[MEMORY MANAGER TYPE]"
#define SBRK_TOTAL "[TOTAL MEMORY ALLOCATED BY SBRK]:"
#define FREED_SIZE "[NO. OF BLOCKS IN FREEDMBLIST]:"
#define ALLOC_SIZE "[NO. OF BLOCKS IN ALLOCMBLIST]:"
#define MEMORY_BLOCK_ADDRESS "[MEMORY BLOCK ADDRESS]:"
#define MEMORY_BLOCK_SIZE "[SIZE]:"
#define MEMORY_BLOCK_CONTENTS "[CONTENTS]:"
#define CONTENTS_STARTING_ADDRESS "[CONTENTS STARTING ADDRESS]:"
#define MERGED "[NO. OF TIMES BLOCKS WERE MERGED]:"
#define SPLIT "[NO. OF TIMES BLOCKS WERE SPLIT]:"

#define LINE_BREAK "********************************************************************************************************************************************" 

/***************************************TYPEDEFS**************************************/

typedef char** memory_address;
typedef list<char*>::iterator char_ptr_iterator;

#endif // UTILS_H