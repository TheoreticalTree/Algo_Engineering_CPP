#include <gtest/gtest.h>
#include <graphgenerator.hpp>
#include <maxcut/basic_maxcut.hpp>
#include <maxcut/your_maxcut.hpp>

#include "graph.hpp"


TEST(MSTTests, MCValueMatchesTest)
{
    Graph g(createMaxCutInstance(100, 1000, 100.0, 42));

    YourMaxCut yourMaxCut(g);
    yourMaxCut.run();

    std::vector<bool> result = yourMaxCut.getResult();

    double true_result = 0.0;

    for (edge e : g.getEdges()) {
        if (result[e.v] != result[e.w]) {
            true_result += e.weight;
        }
    }

    EXPECT_FLOAT_EQ(true_result, yourMaxCut.getMaxCutValue());
}

