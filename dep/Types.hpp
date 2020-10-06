
#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <list>
#include <string>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
using std::string;
using std::list;
using std::cin;
using std::ifstream;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;


typedef char** memory_address;
typedef list<char*>::iterator char_ptr_iterator;

#endif // TYPES_H