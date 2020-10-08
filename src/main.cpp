#include "../dep/main.hpp"

int main(int argc, char const *argv[])
{
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
    } 
    // else if(method == BEST_FIT) {
    //     memoryManager = make_shared<BestFit>(data);
    // } else if(method == WORST_FIT) {
    //     memoryManager = make_shared<WorstFit>(data);
    // }
    memoryManager->run(1000,500);
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
