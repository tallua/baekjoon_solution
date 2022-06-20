#include <gtest/gtest.h>


using Distance = int;
using Node = std::size_t;
struct Edge {
    Node node;
    Distance distance;
};
using Graph = std::vector<std::vector<Edge>>;


extern Distance almost_min_path(Graph& g, Node S, Node D);


namespace {

TEST(TC, TC1)
{
    Graph g {
        {{1, 1}, {2, 1}, {3, 2}, {4, 3}},
        {{5, 2}},
        {{6, 4}},
        {{6, 2}},
        {{6, 4}},
        {{6, 1}},
        {}
    };

    EXPECT_EQ(5, almost_min_path(g, 0, 6));
}

TEST(TC, TC2)
{
    Graph g {
        {{1, 1}},
        {{2, 1}, {3, 1}},
        {{0, 3}},
        {{2, 1}, {0, 2}},
    };

    EXPECT_EQ(-1, almost_min_path(g, 0, 2));
}

TEST(TC, TC3)
{
    Graph g {
        {{1, 1}, {2, 2}, {3, 3}},
        {},
        {{5, 3}},
        {{4, 2}, {0, 1}},
        {{1, 1}},
        {{1, 1}}
    };

    EXPECT_EQ(6, almost_min_path(g, 0, 1));
}


}