#include <gtest/gtest.h>
#include <graphgenerator.hpp>

// Very basic test
TEST(ExampleTests, reallyBasicTest) {
    EXPECT_EQ(1, 1);
}

TEST(ExampleTests, graphCreationTest)
{
    std::vector<edge> edgelist = createValidTopSortInstance(5,3,1);

}