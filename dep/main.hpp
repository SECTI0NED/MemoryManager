#include "Types.hpp"
#include "MemoryManager.hpp"
#include "FirstFit.hpp"

#define FIRST_FIT "ff"
#define BEST_FIT "bf"
#define WORST_FIT "wf"

#define ALLOCATE 1000
#define FREE 500


/* For handling the Memory Manager*/
void handleMemoryManager(list<char*>* data, string method);

/* File Handling */
bool fileExists(string filename);
void read(list<char*>* data, string filename);

/* For printing error messages. */
void printHelpMessage();
void printFileNotFoundMessage(string filename);