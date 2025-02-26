//
// Created by michaelk on 05.01.25.
//

#include <graph.hpp>
#include <iostream>
#include <topsort/basic_topsort.hpp>

#include "../data/topsort/topsort_instance_generator.hpp"

int main(int argc, char** argv) {
    std::cout << "Hello World!" << std::endl;

    std::vector<edge> edgelist = readDimacsFormat("../data/topsort/tiny/TinyInvalid1.txt");
    Graph g(edgelist,true, false);
    BasicTopsort basic_topsort = BasicTopsort(g);
    basic_topsort.run();
    std::cout << basic_topsort.getK();
}
