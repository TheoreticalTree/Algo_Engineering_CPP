#include <gtest/gtest.h>
#include <graphgenerator.hpp>

#include <iostream>
#include <topsort/basic_topsort.hpp>
#include <topsort/topsort_checker.hpp>

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

    for (node v : g.getNodes()) {
        std::cout << "Has node " << v << std::endl;
    }

    for (edge e : g.getEdges()) {
        std::cout << "Edge from " << e.v << " to " << e.w << " with weight " << e.weight << std::endl;
    }

    g.deleteVertex(3);
    g.deleteEdge(0,1);

    for (node v : g.getNodes()) {
        std::cout << "Has node " << v << std::endl;
    }

    for (edge e : g.getEdges()) {
        std::cout << "Edge from " << e.v << " to " << e.w << " with weight " << e.weight << std::endl;
    }
}

TEST(ExampleTests, basicUndirectedGraphTest) {
    Graph g(5, false, true);

    g.addEdge({0,1,3.0});
    g.addEdge({2,1,-1.5});
    g.addEdge({4,1,0.2});
    g.addEdge({0,3,1.2});

    for (node v : g.getNodes()) {
        std::cout << "Has node " << v << std::endl;
    }

    for (edge e : g.getEdges()) {
        std::cout << "Edge from " << e.v << " to " << e.w << " with weight " << e.weight << std::endl;
    }

    g.deleteVertex(3);
    g.deleteEdge(0,1);

    for (node v : g.getNodes()) {
        std::cout << "Has node " << v << std::endl;
    }

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
    Graph g(edgelist);
    BasicTopsort basic_topsort = BasicTopsort(g);
    basic_topsort.run();
    TopSortChecker top_sort_checker = TopSortChecker(g, basic_topsort.getResult(), basic_topsort.getK());
    top_sort_checker.run();
    EXPECT_TRUE(top_sort_checker.certificateIsCorrect());

}
TEST(ExampleTests, InValidTopsortCreationTest)
{
    int n= 10000;
    int targetEdgeNumber = 3000;
    int seed= 1;
    std::vector<edge> edgelist = createInvalidTopSortInstance(n,targetEdgeNumber,seed);
    EXPECT_LE(targetEdgeNumber*0.95,edgelist.size());
    EXPECT_LE(edgelist.size(),targetEdgeNumber*1.05);
    Graph g(edgelist);
    BasicTopsort basic_topsort = BasicTopsort(g);
    basic_topsort.run();
    TopSortChecker top_sort_checker = TopSortChecker(g, basic_topsort.getResult(), basic_topsort.getK());
    top_sort_checker.run();
    EXPECT_TRUE(top_sort_checker.certificateIsCorrect());
    EXPECT_EQ(basic_topsort.getK(),-1);
    EXPECT_TRUE(basic_topsort.getResult().empty());
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
