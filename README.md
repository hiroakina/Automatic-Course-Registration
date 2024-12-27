# Automatic-Course-Registration
The program enables students at BME to create a schedule so that students can take the classes they want to take at a particular time at that time, and take as few classes as possible at the time they want to leave the designated free time open by using maximum matching of bipartite graphs.

## Features

- Load class data from a file containing subject data.
- Add new subjects to be taken in the file
- Specify class preferences and free time.
- Automatically generate an optimal schedule.
- Save and display class data.

## Installation
### Requirements
- A C++ compiler (e.g., g++).

### Compilation
Use the following command to compile the program:
```
g++ -o main main.cpp register.cpp BipartiteMatching.cpp
```
### Execution
Run the program using:
```
./main
```

## Project Structure
- Main Program (main.cpp): Contains user interface and scheduling logic.
- Class Management (register.h, register.cpp): Manages class details.
- Matching Algorithm (BipartiteMatching.h, BipartiteMatching.cpp): Implements the maximum bipartite matching algorithm.
