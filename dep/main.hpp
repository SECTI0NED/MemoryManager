#include "Utils.hpp"
#include "MemoryManager.hpp"
#include "FirstFit.hpp"
#include "BestFit.hpp"
#include "WorstFit.hpp"



/* For handling the Memory Manager*/
void handleMemoryManager(string filename, string method);

/* File Handling */
bool fileExists(string filename);;

/* For printing error messages. */
void printHelpMessage();
void printFileNotFoundMessage(string filename);