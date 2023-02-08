# SearchEngine
# What is it?
It is console application, which can index text files, search requested text in files and output results sorted by relevance.
# What technologies are used?
* C++
* MinGW
* Nlohmann JSON
* Google test
# How to build and launch it?
0. Envornment variable PATH must contain path to the MinGW binary directory and to the CMake binary directory.
1. Build.
```
    cmake -S . -B "build" -G "MinGW Makefiles"
    cmake --build build
```
2. Copy **config.json** file, **requests.json** file and **resources** directory to **build** directory.
3. Launch.
```
    cd build
    search_engine.exe
```
4. Watch results in **answers.json** file.