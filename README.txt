How to execute code on each data set:

Type in console: ./run_firstnames.sh
This runs all algorithms with first-names.txt.

Type in console: ./run_middlenames.sh
This runs all algorithms with middle-names.txt.

*********************************************************
How to run and compile source code:

Type: make clean
Type: make
The program file is 'program', it requires 2 arguments to run:
Format: ./program [filename] [algorithm]
First argument: filename of which the algorithm uses (destination should be relative to the Makefile).
Second argument: algorithm - which is either 'ff' (First Fit), 'bf' (Best Fit), or 'wf' (Worst Fit).

Example: ./program _data/first-names.txt ff

**********************************************************
Introduction to source code:

main.cpp:
- This class decides which algorithm to perform based on the arguments (ff, bf, and wf)
- Also checks the file exists in the arguments.

Utils.hpp:
- Contains preprocessing directives such as #includes and #defines used throughout the project.
- Note that it also has the constants 'ALLOC' and 'FREE' which define the number of blocks to be allocated and freed in each cycle.

MemoryManager.cpp & MemoryManager.hpp:
- Is the parent class of all the algorithm classes: FirstFit.cpp, BestFit.cpp, WorstFit.cpp.
- Contains crucial methods for each child class such as:
    - freeing blocks.
    - allocating blocks (has polymorphic property through retrieveBlock()).
    - merging blocks if they are adjacent in memory.
    - splitting blocks.
    - printing details.

MemoryBlock.cpp & MemoryBlock.hpp:
- Represents a memory block/node in either freedMBList or allocMBList.
- Contains data allocated by sbrk.

FirstFit.cpp & FirstFit.hpp:
- Performs the first fit algorithm.
- Uses polymorphic method retrieveBlock() to perform its algorithm.

BestFit.cpp & BestFit.hpp:
- Performs the best fit algorithm.
- Uses polymorphic method retrieveBlock() to perform its algorithm.

WorstFit.cpp & WorstFit.hpp:
- Performs the worst fit algorithm.
- Uses polymorphic method retrieveBlock() to perform its algorithm.


