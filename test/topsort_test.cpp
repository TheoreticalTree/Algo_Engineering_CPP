// Created by kathy on 24.02.25.
//

#include <gtest/gtest.h>
#include <graphgenerator.hpp>
#include <topsort/basic_topsort.hpp>
#include <topsort/topsort_checker.hpp>
#include <topsort/your_topsort.hpp>

#include "graph.hpp"


TEST(TopSortTests, LineTest)
{
    Graph g(3, true, false);
    g.addEdge({2, 1});
    g.addEdge({1, 0});
    YourTopsort your_topsort = YourTopsort(g);
    your_topsort.run();
    std::vector<node> result = your_topsort.getResult();
    EXPECT_EQ(your_topsort.getK(),3);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 1);
}

TEST(TopSortTests, CircleTest)
{
    Graph g(3, true, false);
    g.addEdge({0, 1});
    g.addEdge({1, 2});
    g.addEdge({2,0});
    YourTopsort your_topsort = YourTopsort(g);
    your_topsort.run();
    std::vector<node> result = your_topsort.getResult();
    EXPECT_EQ(your_topsort.getK(),-1);
    EXPECT_TRUE(result.empty());
}

TEST(TopSortTests, NoRunYet)
{
    Graph g(3,true, false);
    g.addEdge({0, 1});
    g.addEdge({1, 2});
    g.addEdge({2,0});
    YourTopsort your_topsort = YourTopsort(g);
    EXPECT_THROW(your_topsort.getResult(),std::runtime_error);
    EXPECT_THROW(your_topsort.getK(), std::runtime_error);
}
TEST(TopSortTests, SeveralPredecessors)
{
    Graph g(7, true, false);
    g.addEdge({0,1});
    g.addEdge({0,2});
    g.addEdge({1,2});
    g.addEdge({1,3});
    g.addEdge({1,4});
    g.addEdge({1,5});
    g.addEdge({2,3});
    g.addEdge({2,4});
    g.addEdge({2,6});
    g.addEdge({3,6});
    g.addEdge({5,6});
    g.addEdge({6,4});
    YourTopsort your_topsort = YourTopsort(g);
    your_topsort.run();
    std::vector<node> result = your_topsort.getResult();
    EXPECT_EQ(your_topsort.getK(), 6);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],2);
    EXPECT_EQ(result[2],3);
    EXPECT_EQ(result[3],4);
    EXPECT_EQ(result[4],6);
    EXPECT_EQ(result[5],3);
    EXPECT_EQ(result[6],5);
}
