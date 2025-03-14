//
// Created by michaelk on 09.03.25.
//

#include <cstring>
#include <iostream>

#include "../data/topsort/topsort_instance_generator.hpp"
#include "../data/mst/mst_instance_generator.hpp"
#include "../data/maxcut/maxcut_instance_generator.hpp"

int main(int argc, char** argv) {
    if (argc >= 2) {
        if (std::strcmp(argv[1], "topsort") == 0) {
            topsortInstanceGenerator();
        }
        else if (std::strcmp(argv[1], "mst") == 0) {
            mstInstanceGenerator();
        }
        else if (std::strcmp(argv[1], "maxcut") == 0) {
            maxcutInstanceGenerator();
        }
        else {
            std::cout << "Does not recognize argument" << argv[0] << ", please call with either topsort, mst or maxcut as an arg or no arg at all" << std::endl;
        }
    }
    else {
        topsortInstanceGenerator();
        mstInstanceGenerator();
        maxcutInstanceGenerator();
    }
}
