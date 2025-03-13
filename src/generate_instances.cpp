//
// Created by michaelk on 09.03.25.
//

#include <cstring>
#include <iostream>

#include "../data/topsort/topsort_instance_generator.hpp"
#include "../data/mst/mst_instance_generator.hpp"
#include "../data/maxcut/maxcut_instance_generator.hpp"

int main(int argc, char** argv) {
    if (argc == 1) {
        if (std::strcmp(argv[0], "topsort") == 0) {
            topsortInstanceGenerator();
        }
        else if (std::strcmp(argv[0], "mst") == 0) {
            mstInstanceGenerator();
        }
        else if (std::strcmp(argv[0], "maxcut") == 0) {
            maxcutInstanceGenerator();
        }
        else {
            std::cout << "Please call with either topsort, mst or maxcut as an arg or no arg at all" << std::endl;
        }
    }
    else {
        topsortInstanceGenerator();
        mstInstanceGenerator();
        maxcutInstanceGenerator();
    }
}
