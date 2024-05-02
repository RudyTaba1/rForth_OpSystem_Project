## Introduction

The Goal of this rForth Project is to achieve the following functionality:
-  Boolean
-  Variable
-  Loop
-  Interpreter

Together, we will complete these functionalities. Zefan will be in charge of Variable and Boolean
Functionality and Rudy will be in charge of Loop and Interpreter Functionality.

## Functionality

- Boolean 
    - And
    - Or
    - Invert
    - less than (<)
    - greater than (>)
    - equal to (=)
- Stack Manipulation
    - dup
    - swap
    - over
    - rot
    - pop
- Arithmetic Operations
    - addition (+)
    - multiplicaion (*)
    - division (/)
    - subtraction(-)
    - Finding remainders when dividing (mod)
- Variable storage
    - STILL A WORK IN PROGRESS
    - 10 var hello stores 10 at variable hello
    - currently only stores a value of one (idk why)

## Compilation/Startup

1) Install CMake
```bash
  sudo apt install cmake -y
```
2) Create a shell sctipt called buildScript.sh with the following commands:
```bash
  #!/bin/bash
  cd rForthProject

  cmake -S . -B build

  cmake --build build

  cd ..

  cmake -S . -B build
  
  cmake --build build

  cd build/bin

  ls
```
3) Give buildScript.sh execution power
```bash
  chmod +x buildScript.sh
```
4) Run buildScript.sh
```bash
  ./buildScript.sh
```
5) When compiled run the rForthInterpreter
```bash
  ./build/bin/rForthInterpreter
```

## Authors

- [Rudy Tabachnik](https://github.com/RudyTaba1)
- [Zefan Amare](https://github.com/zamare)
