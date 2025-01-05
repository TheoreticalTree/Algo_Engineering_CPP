//
// Created by michaelk on 05.01.25.
//

#include <cstdint>

#ifndef ALGO_ENGINEERING_CPP_BASE_HPP
#define ALGO_ENGINEERING_CPP_BASE_HPP

using node = uint32_t;
using count = uint32_t;
using edgeWeight = double;

struct edge {
    node v, w;
    edgeWeight weight;
};

#endif //ALGO_ENGINEERING_CPP_BASE_HPP
