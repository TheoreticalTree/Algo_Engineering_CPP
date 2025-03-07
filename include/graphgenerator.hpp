//
// Created by kathy on 05.01.25.
//

#ifndef GRAPHGENERATOR_HPP
#define GRAPHGENERATOR_HPP
#include <base.hpp>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include <algorithm>

inline std::vector<edge> createValidTopSortInstance(int n, int targetEdgeNumber, int seed)
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
    std::iota(std::begin(nodes), std::end(nodes), 1);
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

inline std::vector<edge> createInvalidTopSortInstance(int n, int targetEdgeNumber, int seed)
{
    uint64_t maxEdgeNumber = n * (n - 1);
    if (targetEdgeNumber > maxEdgeNumber)
    {
        throw std::runtime_error("Number of edges is too high. For n =" + std::to_string(n)
            + " select at most " + std::to_string(maxEdgeNumber) + " edges!\n");
    }
    double edgesInCircles = 0;
    std::vector<node> nodes = std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 1);
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

inline std::vector<edge> createValidMSTInstance(int n, int targetEdgeNumber, double maximumWeight, int seed)
{
    bool edgeIsDouble = true;
    int maxEdgeNumber = n * (n - 1) / 2;
    if (targetEdgeNumber > maxEdgeNumber || targetEdgeNumber < n - 1)
    {
        throw std::runtime_error(
            "Number of edges is wrong. For n = " + std::to_string(n) + " select at least " + std::to_string(n - 1) +
            " and at most " + std::to_string(maxEdgeNumber) + " edges!\n");
    }
    std::vector<node> nodes = std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 1);
    std::vector<edge> edgelist;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> randomWeight(-maximumWeight, maximumWeight);;
    srand(seed);
    int i, j, temp, sign;
    double random;
    for (int k = 0; k < 2 * n; k++)
    {
        i = rand() % n;
        j = rand() % n;
        temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    std::vector<node> isConnected;
    std::vector<node> isNotConnected = std::vector<node>(n);
    std::iota(isNotConnected.begin(), isNotConnected.end(), 0);
    i = rand() % isNotConnected.size();
    isConnected.push_back(isNotConnected[i]);
    isNotConnected.erase(isNotConnected.begin() + i);
    for (int k = 0; k < n - 1; k++)
    {
        i = rand() % isConnected.size();
        j = rand() % isNotConnected.size();
        edgelist.push_back(edge(nodes[isConnected[i]], nodes[isNotConnected[j]], randomWeight(gen)));
        isConnected.push_back(isNotConnected[j]);
        isNotConnected.erase(isNotConnected.begin() + j);
    }
    double edgeRatio = static_cast<double>(targetEdgeNumber - n + 1) / static_cast<double>(maxEdgeNumber);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            random = rand() / double(RAND_MAX);
            if (random <= edgeRatio)
            {
                /* for (int k = 0; k < n - 1; k++)
                 {
                     if ((edgelist[k].v == nodes[i] && edgelist[k].w == nodes[j]) || (edgelist[k].v == nodes[j] &&
                         edgelist[k].w == nodes[i]))
                     {
                         edgeIsDouble = true;
                     }
                 }

                 if (!edgeIsDouble)
                 {
                 */
                edgelist.push_back(edge(nodes[i], nodes[j], randomWeight(gen)));
            //}edgeIsDouble=false;
            }
        }
    }
    return edgelist;
}

#endif //GRAPHGENERATOR_HPP
