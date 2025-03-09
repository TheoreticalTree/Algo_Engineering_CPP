# README

## Build
1) Clone the project
2) run ```git submodule update --init --recursive```
3) run ```cmake -B build``` and ```cmake --build build``` to build the instance generator, tests and benchmark skripts

## Implement your own code
1) Implement topsort code in ```src/your_topsort.cpp``` and mst code in ```src/your_mst.cpp```. The respective headers for the classes are ```include/your_topsort.hpp``` and ```include/your_mst.hpp```
2) If you want to implement multiple algorithms solving the same problem, remember to add the files to ```CMakeLists.txt``` and to the benchmark code in ```src/benchmark_X.cpp```

## Generate Instances
**WARNING:** We assume that the base directory is the directory from which all code is executed. Many IDEs set the directory from which code is executed to *build* instead, which means the code doesn't find instance files where it expects them to be.
1) Run ```./build/build_instances``` to generate instances for Topological Sort and Minimum Spanning Tree (this may take a minute or two)

## Run Tests
**WARNING:** We assume that the base directory is the directory from which all code is executed. Many IDEs set the directory from which code is executed to *build* instead, which means the code doesn't find instance files where it expects them to be.
1) Run ```./build/test/X``` where X is the appropriate test you want to run
2) This will automatically run the tests for the related problem on your algorithm implementation

## Run Benchmarks
**WARNING:** We assume that the base directory is the directory from which all code is executed. Many IDEs set the directory from which code is executed to *build* instead, which means the code doesn't find instance files where it expects them to be.
1) Run ```./build/benchmark_X``` to run the benchmark for X
2) Run ```python3 plot_X.py``` to plot the results of running X
