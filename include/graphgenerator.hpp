//
// Created by kathy on 05.01.25.
//

#ifndef GRAPHGENERATOR_HPP
#define GRAPHGENERATOR_HPP
#include <base.hpp>
#include <cstdint>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>


inline std::vector<edge> createValidTopSortInstance(uint64_t n, int targetEdgeNumber, int seed)
{
    uint64_t maxEdgeNumber = n * (n - 1) / 2;
    if (targetEdgeNumber > maxEdgeNumber)
    {
        throw std::runtime_error(
            "Number of edges is too high. For n = " + std::to_string(n) + " select at most " +
            std::to_string(maxEdgeNumber) + " edges!\n");
    }
    double edgeRatio = static_cast<double>(targetEdgeNumber) / static_cast<double>(maxEdgeNumber);
    std::vector<node> nodes = std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 0);
    std::vector<edge> edgelist;
    srand(seed);
    int i, j, temp;
    double random;
    for (int v = n - 1; v > 0; v--)
    {
        std::swap(nodes[v], nodes[rand() % v]);
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            random = rand() / double(RAND_MAX);
            if (random <= edgeRatio)
            {
                edgelist.emplace_back(nodes[i], nodes[j], 1);
            }
        }
    }
    return edgelist;
}

inline std::vector<edge> createInvalidTopSortInstance(uint64_t n, int targetEdgeNumber, int seed)
{
    uint64_t maxEdgeNumber = n * (n - 1);
    if (targetEdgeNumber > maxEdgeNumber)
    {
        throw std::runtime_error("Number of edges is too high. For n =" + std::to_string(n)
            + " select at most " + std::to_string(maxEdgeNumber) + " edges!\n");
    }
    double edgesInCircles = 0;
    std::vector<node> nodes = std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 0);
    std::vector<edge> edgelist;
    srand(seed);
    int i, j, temp;
    double random;
    for (int v = n - 1; v > 0; v--)
    {
        std::swap(nodes[v], nodes[rand() % v]);
    }
    int circlesize = (rand() % (n / 2)) + 1;
    double edgeRatio = static_cast<double>(targetEdgeNumber - circlesize) / static_cast<double>(maxEdgeNumber);

    for (int v = 0; v < circlesize; v++) {
        edgelist.emplace_back(nodes[v], nodes[v + 1], 1);
    }

    edgelist.emplace_back(nodes[circlesize], nodes[0]);

    for (int v = 0; v < n; v++) {
        for (int w = 0; w < n; w++) {
            if ((v == w) || ((std::abs(v - w) == 1) && w <= circlesize))
                continue;

            
            random = rand() / double(RAND_MAX);
            if (random <= edgeRatio)
            {
                edgelist.push_back(edge(nodes[v], nodes[w], 1));
            }
        }
    }

    return edgelist;
}

inline std::vector<edge> createValidMSTInstance(uint64_t n, int targetEdgeNumber, double maximumWeight, int seed)
{
    bool edgeIsDouble = true;
    uint64_t maxEdgeNumber = n * (n - 1) / 2;
    if (targetEdgeNumber > maxEdgeNumber || targetEdgeNumber < n - 1)
    {
        throw std::runtime_error(
            "Number of edges is wrong. For n = " + std::to_string(n) + " select at least " + std::to_string(n - 1) +
            " and at most " + std::to_string(maxEdgeNumber) + " edges!\n");
    }

    double edgeRatio = static_cast<double>(targetEdgeNumber) / static_cast<double>(maxEdgeNumber);
   
    std::vector<node> nodes = std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 0);

    std::vector<node> components = std::vector<node>(n);
    std::iota(std::begin(components), std::end(components), 0);

    std::vector<std::vector<int>> in_component;

    for (int i = 0; i < n; i++) {
        in_component.emplace_back(1, i);
    }
    
    std::vector<edge> edgelist;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> randomWeight(-maximumWeight, maximumWeight);;
    srand(seed);
    int i, j, temp, sign;
    double random;

    for (int v = n - 1; v > 0; v--)
    {
        std::swap(nodes[v], nodes[rand() % v]);
    }

    for (int v = 0; v < n; v++) {
        for (int w = v + 1; w < n; w++) {
            
            random = rand() / double(RAND_MAX);
            if (random <= edgeRatio)
            {
                edgelist.push_back(edge(nodes[v], nodes[w], randomWeight(gen)));
                

                if (components[v] != components[w]) {
                    int rep_v = components[v], rep_w = components[w];

                    if (in_component[rep_v].size() < in_component[rep_w].size()) {
                        std::swap(rep_v, rep_w);
                    }

                    for (int x : in_component[rep_w]) {
                        components[x] = rep_v;
                        in_component[rep_v].emplace_back(x);
                    }

                    in_component[rep_w].clear();
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (components[0] != components[i]) {
            edgelist.push_back(edge(nodes[0], nodes[i], randomWeight(gen)));

             
            int rep_v = components[0], rep_w = components[i];

            if (in_component[rep_v].size() < in_component[rep_w].size()) {
                std::swap(rep_v, rep_w);
            }

            for (int x : in_component[rep_w]) {
                components[x] = rep_v;
                in_component[rep_v].emplace_back(x);
            }

            in_component[rep_w].clear();
        }
    }

    return edgelist;
}

#endif //GRAPHGENERATOR_HPP
