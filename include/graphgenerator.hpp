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

std::vector<edge> createValidTopSortInstance(int n, int targetEdgeNumber, int seed)
{
    int maxEdgeNumber = n * (n-1)/2;
    if (targetEdgeNumber>maxEdgeNumber)
    {
        throw std::runtime_error("Number of edges is too high. For n = " + std::to_string(n) + " select at most " + std::to_string(maxEdgeNumber) + " edges!\n");
    }
    double edgeRatio = static_cast<double>(targetEdgeNumber) / static_cast<double>(maxEdgeNumber);
    std::vector<node> nodes= std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 1);
    std::vector<edge> edgelist;
    srand(seed);
    int i,j,temp;
    double random;
    for (int k = 0; k < 2*n; k++)
    {
        i = rand() % n;
        j = rand() % n;
        temp = nodes[i];
        nodes[i]=nodes[j];
        nodes[j]= temp;
    }
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            random = rand() / double(RAND_MAX);
            if(random<= edgeRatio)
            {
                edgelist.push_back(edge(nodes[i],nodes[j],1));
            }
        }
    }
    return edgelist;
}
std::vector<edge> createInvalidTopSortInstance(int n, int targetEdgeNumber, int seed)
{
    int maxEdgeNumber = n * (n-1)/2;
    if (targetEdgeNumber>maxEdgeNumber)
    {
        throw std::runtime_error("Number of edges is too high. For n =" + std::to_string(n)
            + " select at most " + std::to_string( maxEdgeNumber) +" edges!\n");
    }
    double edgesInCircles = 0;
    std::vector<node> nodes= std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 1);
    std::vector<edge> edgelist;
    srand(seed);
    int i,j,temp;
    double random;
    for (int k = 0; k < 2*n; k++)
    {
        i = rand() % n;
        j = rand() % n;
        temp = nodes[i];
        nodes[i]=nodes[j];
        nodes[j]= temp;
    }
    int circlesize = rand()% targetEdgeNumber;
    std::vector<bool> isInCircle = std::vector<bool>(n);
    i= rand() %n;
    int start= i;
    isInCircle[i]=true;
    for (int k = 0; k < circlesize-1; k++)
    {
        j= rand() %n;
        if (!isInCircle[j])
        {
            edgelist.push_back(edge(nodes[i],nodes[j],1));
        }
        i=j;
    }
    edgelist.push_back(edge(i,start,1));

    double edgeRatio = static_cast<double>(targetEdgeNumber-circlesize)/static_cast<double>(maxEdgeNumber);
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            random = rand() / double(RAND_MAX);
            if (random <= edgeRatio && (std::find(edgelist.begin(), edgelist.begin()+circlesize+1, edge(nodes[i],nodes[j],1))==edgelist.begin()+circlesize+1) && (find(edgelist.begin(), edgelist.begin()+(circlesize+1), edge(nodes[j],nodes[i],1)))==edgelist.begin()+(circlesize+1))
            {
                edgelist.push_back(edge(nodes[i],nodes[j],1));
            }
        }
    }
    return edgelist;
}
std::vector<edge> createValidMSTInstance(int n, int targetEdgeNumber, double maximumWeight, int seed)
{
    int maxEdgeNumber = n * (n-1)/2;
    if (targetEdgeNumber>maxEdgeNumber|| targetEdgeNumber<n-1)
    {
        throw std::runtime_error("Number of edges is wrong. For n = " + std::to_string(n) + " select at least " + std::to_string(n-1) +" and at most " + std::to_string(maxEdgeNumber) + " edges!\n");
    }
    std::vector<node> nodes= std::vector<node>(n);
    std::iota(std::begin(nodes), std::end(nodes), 1);
    std::vector<edge> edgelist;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> randomWeight(-maximumWeight, maximumWeight);;
    srand(seed);
    int i,j,temp, sign;
    double random;
    for (int k = 0; k < 2*n; k++)
    {
        i = rand() % n;
        j = rand() % n;
        temp = nodes[i];
        nodes[i]=nodes[j];
        nodes[j]= temp;
    }

    std::vector<node> isConnected;
    std::vector<node> isNotConnected= std::vector<node>(n);
    i= rand() % isNotConnected.size();
    isConnected.push_back(isNotConnected[i]);
    isNotConnected.erase(isNotConnected.begin()+i);
    for (int k = 0; k < n-1; k++)
    {
        i= rand() % isConnected.size();
        j= rand() % isNotConnected.size();
        edgelist.push_back(edge(nodes[isConnected[i]],nodes[isNotConnected[j]], randomWeight(gen)));
        isConnected.push_back(isNotConnected[j]);
        isNotConnected.erase(isNotConnected.begin()+j);
    }
    double edgeRatio = static_cast<double>(targetEdgeNumber-n+1) / static_cast<double>(maxEdgeNumber);
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            random = rand() / double(RAND_MAX);
            if(random<= edgeRatio){
                edgelist.push_back(edge(nodes[i],nodes[j], randomWeight(gen)));
            }
        }
    }
    return edgelist;
}

#endif //GRAPHGENERATOR_HPP
