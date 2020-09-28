#include "../dep/main.hpp"

int main(int argc, char const *argv[])
{
    list<char*> data;
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
            read(&data, filename);
            if(method != FIRST_FIT && method != BEST_FIT && method != WORST_FIT) {
                printHelpMessage();
                return EXIT_FAILURE;
            } else {
                handleMemoryManager(&data, method);
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

void read(list<char*>* data, string filename) {
    ifstream stream(filename);
    string line = "";
    while(!stream.eof()){
        stream >> line;
        char cstring[line.size()];
        strcpy(cstring, line.c_str());
        data->push_back(cstring);
    }
    stream.close();
}

void handleMemoryManager(list<char*>* data, string method) {
    shared_ptr<MemoryManager> memoryManager = nullptr;
    if(method == FIRST_FIT){
        memoryManager = make_shared<FirstFit>(data);
    } 
    // else if(method == BEST_FIT) {
    //     memoryManager = make_shared<BestFit>(data);
    // } else if(method == WORST_FIT) {
    //     memoryManager = make_shared<WorstFit>(data);
    // }
    memoryManager->run(ALLOCATE, FREE);
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
