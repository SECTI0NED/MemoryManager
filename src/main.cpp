#include "../dep/main.hpp"

int main(int argc, char const *argv[])
{
 

    // void * request1 = sbrk(5);
    // int* startingAddress1 = (int*) request1;

    // void * request2 = sbrk(10);
    // int* startingAddress2 = (int*) request2;

    // // Compare
    // char* endAddress1 = (char*) request1 + 5;

    // cout << startingAddress1 << endl;

    // cout << "This address: " << (int*) endAddress1 << endl << "Should be the same as " << startingAddress2 << endl;
    // bool equal = ((int*) endAddress1) == (startingAddress2);
    // cout << "Equal: " << equal << endl;


    if(argc <= 2){
        printHelpMessage();
        return EXIT_FAILURE;
    } else {
        string filename = argv[1];
        string method = argv[2];
        bool fExists = fileExists(filename);
        if(!fExists){
            printFileNotFoundMessage(filename);
            return EXIT_FAILURE;
        } else {
            if(method != FIRST_FIT && method != BEST_FIT && method != WORST_FIT) {
                printHelpMessage();
                return EXIT_FAILURE;
            } else {
                handleMemoryManager(filename, method);
            }
        }
    }
    return EXIT_SUCCESS;
}

bool fileExists(string filename){
    bool exists = false;
    ifstream stream(filename);
    if(stream.good()){
        exists = true;
    }
    stream.close();
    return exists;
}


void handleMemoryManager(string filename, string method) {

    MemoryManager* memoryManager = nullptr;
    if(method == FIRST_FIT){
        memoryManager = new FirstFit(filename);
    } else if(method == BEST_FIT) {
        memoryManager = new BestFit(filename);
    } else if(method == WORST_FIT) {
        memoryManager = new WorstFit(filename);
    }
    memoryManager->run(ALLOCATE,FREE);
    delete memoryManager;
}

/*********************************** Error Messages ***********************************/

void printHelpMessage() {
    cout << "Error: Invalid Format." << endl
         << "\tFormat: ./program [filename] [method]" << endl
         << "\t[method]: ff | bf | wf " << endl
         << "\tff = First Fit" << endl
         << "\tbf = Best Fit" << endl
         << "\twf = Worst Fit" << endl;
}

void printFileNotFoundMessage(string filename) {
    cout << "Error: File '" << filename << "' Not Found." << endl;
}


/************************************ Testing ***********************************/


void print(list<char*>* datalist){
    for(char* data : *datalist) {
        cout << data << endl;
    }
}
