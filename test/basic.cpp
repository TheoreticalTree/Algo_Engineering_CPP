#include <gtest/gtest.h>
#include <graphgenerator.hpp>

#include <iostream>

#include "graph.hpp"

// Very basic test
TEST(ExampleTests, reallyBasicTest) {
    EXPECT_EQ(1, 1);
}

TEST(ExampleTests, basicDirectedGraphTest) {
    Graph g(5, true, true);

    g.addEdge({0,1,3.0});
    g.addEdge({1,0,-1.5});
    g.addEdge({4,1,0.2});
    g.addEdge({0,3,1.2});

    for (edge e : g.getEdges()) {
        std::cout << "Edge from " << e.v << " to " << e.w << " with weight " << e.weight << std::endl;
    }
}

TEST(ExampleTests, basicUndirectedGraphTest) {
    Graph g(5, false, true);

    g.addEdge({0,1,3.0});
    g.addEdge({1,0,-1.5});
    g.addEdge({4,1,0.2});
    g.addEdge({0,3,1.2});

    for (edge e : g.getEdges()) {
        std::cout << "Edge from " << e.v << " to " << e.w << " with weight " << e.weight << std::endl;
    }
}

TEST(ExampleTests, ValidTopsortCreationTest)
{
    int n= 1000;
    int targetEdgeNumber = 300;
    int seed= 1;
    std::vector<edge> edgelist = createValidTopSortInstance(n,targetEdgeNumber,seed);
    EXPECT_LE(targetEdgeNumber*0.95,edgelist.size());
    EXPECT_LE(edgelist.size(),targetEdgeNumber*1.05);
}
TEST(ExampleTests, InValidTopsortCreationTest)
{
    int n= 10000;
    int targetEdgeNumber = 3000;
    int seed= 1;
    std::vector<edge> edgelist = createInvalidTopSortInstance(n,targetEdgeNumber,seed);
    EXPECT_LE(targetEdgeNumber*0.95,edgelist.size());
    EXPECT_LE(edgelist.size(),targetEdgeNumber*1.05);
}
TEST(ExampleTests, ValidMSTCreationTest)
{
    int n= 10000;
    int targetEdgeNumber = 3000;
    int seed= 1;
    std::vector<edge> edgelist = createInvalidTopSortInstance(n,targetEdgeNumber,seed);
    EXPECT_LE(targetEdgeNumber*0.95,edgelist.size());
    EXPECT_LE(edgelist.size(),targetEdgeNumber*1.05);
}
