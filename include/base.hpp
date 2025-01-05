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

    friend bool operator==(const edge &a, const edge &b) {
        return (a.v == b.v) && (a.w == b.w);
    }

    friend bool operator!=(const edge &a, const edge &b) {
        return !((a.v == b.v) && (a.w == b.w));
    }
};

#endif //ALGO_ENGINEERING_CPP_BASE_HPP
