## Introduction

The Goal of this rForth Project is to achieve the following functionality:
-  Boolean
-  Variable
-  Loop
-  Interpreter

Together, we will complete these functionalities. Zefan will be in charge of Variable and Boolean
Functionality and Rudy will be in charge of Loop and Interpreter Functionality.

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
  ./rForthInterpreter
```

## Authors

- [Rudy Tabachnik](https://github.com/RudyTaba1)
- [Zefan Amare](https://github.com/zamare)
