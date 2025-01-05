//
// Created by kathy on 05.01.25.
//

#ifndef GRAPHGENERATOR_HPP
#define GRAPHGENERATOR_HPP
#include <base.hpp>
#include <numeric>
#include <stdexcept>
#include <vector>

std::vector<edge> createValidTopSortInstance(int n, int targetEdgeNumber, int seed)
{
    int maxEdgeNumber = n * (n+1)/2;
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
    int maxEdgeNumber = n * (n+1)/2;
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
            if (random <= edgeRatio && (find(edgelist.begin(), edgelist.begin()+circlesize+1, edge(nodes[i],nodes[j],1))==edgelist.begin()+circlesize+1) && (find(edgelist.begin(), edgelist.begin()+(circlesize+1), edge(nodes[j],nodes[i],1)))==edgelist.begin()+(circlesize+1))
            {
                edgelist.push_back(edge(nodes[i],nodes[j],1));
            }
        }
    }
    return edgelist;
}

#endif //GRAPHGENERATOR_HPP
