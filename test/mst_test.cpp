//
// Created by kathy on 26.02.25.
//
#include <gtest/gtest.h>
#include <graphgenerator.hpp>
#include <mst/basic_mst.hpp>
#include <mst/your_mst.hpp>
#include <mst/mst_checker.hpp>

#include "graph.hpp"

TEST(MSTTests, reallyBasicTest)
{
    EXPECT_EQ(1, 1);
}

TEST(MSTTests, LineTest)
{
    Graph g(3, false, true);
    g.addEdge({2, 1, 2});
    g.addEdge({1, 0, 1});
    YourMST basic_mst(g);
    basic_mst.run();
    EXPECT_EQ(basic_mst.getMSTValue(), 3);
    std::vector<edge> result = basic_mst.getResult();
    EXPECT_EQ(result[0].weight, 1);
    EXPECT_EQ(result[1].weight, 2);
}

TEST(MSTTests, CircleTest)
{
    Graph g(3, false, true);
    g.addEdge({0, 1, 1});
    g.addEdge({1, 2, 3.5});
    g.addEdge({2, 0, -2});
    YourMST basic_mst(g);
    basic_mst.run();
    EXPECT_EQ(basic_mst.getMSTValue(), -1);
    std::vector<edge> result = basic_mst.getResult();
    EXPECT_EQ(result[0].weight, -2);
    EXPECT_EQ(result[1].weight, 1);
}

TEST(MSTTests, NoRunYet)
{
    Graph g(3, false, true);
    g.addEdge({0, 1, 1});
    g.addEdge({1, 2, 1});
    g.addEdge({2, 0, 1});
    YourMST basic_mst(g);
    EXPECT_THROW(basic_mst.getResult(), std::runtime_error);
    EXPECT_THROW(basic_mst.getMSTValue(), std::runtime_error);
}

TEST(MSTTests, SeveralPredecessors)
{
    Graph g(7, true, false);
    g.addEdge({0, 1, 1});
    g.addEdge({0, 2, 2});
    g.addEdge({1, 2, 3});
    g.addEdge({1, 3, 4});
    g.addEdge({1, 4, 5});
    g.addEdge({1, 5, 1});
    g.addEdge({2, 3, 1});
    g.addEdge({2, 4, 2});
    g.addEdge({2, 6, 4});
    g.addEdge({3, 6, 4});
    g.addEdge({5, 6, 3});
    g.addEdge({6, 4, 5});
    YourMST basic_mst(g);
    basic_mst.run();
    EXPECT_EQ(basic_mst.getMSTValue(), 10);
    std::vector<edge> result = basic_mst.getResult();
    EXPECT_TRUE(std::find(result.begin(), result.end(), edge({0,1,1})) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), edge({0,2,2})) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), edge({1,5,1})) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), edge({2,3,1})) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), edge({2,4,2})) != result.end());
    EXPECT_TRUE(std::find(result.begin(), result.end(), edge({5,6,3})) != result.end());
}


