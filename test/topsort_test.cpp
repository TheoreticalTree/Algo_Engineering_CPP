// Created by kathy on 24.02.25.
//

#include <gtest/gtest.h>
#include <graphgenerator.hpp>
#include <topsort/basic_topsort.hpp>
#include <topsort/topsort_checker.hpp>

#include "graph.hpp"
TEST(TopSortTests, reallyBasicTest)
{
    EXPECT_EQ(1, 1);
}

TEST(TopSortTests, LineTest)
{
    Graph g(3, true, false);
    g.addEdge({2, 1});
    g.addEdge({1, 0});
    BasicTopsort basic_topsort = BasicTopsort(g);
    basic_topsort.run();
    std::vector<node> result = basic_topsort.getResult();
    EXPECT_EQ(basic_topsort.getK(),3);
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
    BasicTopsort basic_topsort = BasicTopsort(g);
    basic_topsort.run();
    std::vector<node> result = basic_topsort.getResult();
    EXPECT_EQ(basic_topsort.getK(),-1);
    EXPECT_TRUE(result.empty());
}

TEST(TopSortTests, NoRunYet)
{
    Graph g(3,true, false);
    g.addEdge({0, 1});
    g.addEdge({1, 2});
    g.addEdge({2,0});
    BasicTopsort basic_topsort = BasicTopsort(g);
    EXPECT_THROW(basic_topsort.getResult(),std::runtime_error);
    EXPECT_THROW(basic_topsort.getK(), std::runtime_error);
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
    BasicTopsort basic_topsort = BasicTopsort(g);
    basic_topsort.run();
    std::vector<node> result = basic_topsort.getResult();
    EXPECT_EQ(basic_topsort.getK(), 6);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],2);
    EXPECT_EQ(result[2],3);
    EXPECT_EQ(result[3],4);
    EXPECT_EQ(result[4],6);
    EXPECT_EQ(result[5],3);
    EXPECT_EQ(result[6],5);
}

TEST(TopSortTests, CertificateInvalidOnValidSolution)
{
    Graph g(3, true, false);
    g.addEdge({2, 1});
    g.addEdge({1, 0});
    TopSortChecker top_sort_checker = TopSortChecker(g,{},-1);
    top_sort_checker.run();
    EXPECT_FALSE(top_sort_checker.certificateIsCorrect());
    TopSortChecker top_sort_checker2 = TopSortChecker(g, {3,2,1},-1);
    top_sort_checker2.run();
    EXPECT_FALSE(top_sort_checker2.certificateIsCorrect());
    TopSortChecker top_sort_checker3 = TopSortChecker(g,{},3);
    top_sort_checker3.run();
    EXPECT_FALSE(top_sort_checker3.certificateIsCorrect());
}

TEST(TopSortTests, CertificateInvalidOnInvalidSolution)
{
    Graph g(3, true, false);
    g.addEdge({0, 1});
    g.addEdge({1, 2});
    g.addEdge({2,0});
    TopSortChecker top_sort_checker = TopSortChecker(g,{1,2,3},3);
    top_sort_checker.run();
    EXPECT_FALSE(top_sort_checker.certificateIsCorrect());
    TopSortChecker top_sort_checker2 = TopSortChecker(g, {3,2,1},-1);
    top_sort_checker2.run();
    EXPECT_FALSE(top_sort_checker2.certificateIsCorrect());
    TopSortChecker top_sort_checker3 = TopSortChecker(g,{},3);
    top_sort_checker3.run();
    EXPECT_FALSE(top_sort_checker3.certificateIsCorrect());
}
TEST(TopSortTests, ValidCertificateWithSeveralPredecessors)
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
    TopSortChecker top_sort_checker = TopSortChecker(g,{1,2,3,4,6,3,5},6);
    top_sort_checker.run();
    EXPECT_TRUE(top_sort_checker.certificateIsCorrect());
}