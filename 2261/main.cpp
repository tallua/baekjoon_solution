#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;
using coord_t = int;

struct vec2
{
    coord_t x, y;
};

struct CompareYX
{
    constexpr bool operator()(const vec2 &lhs, const vec2 &rhs) const
    {
        return lhs.y == rhs.y ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
};

template <typename T>
constexpr T pow2(const T &val)
{
    return val * val;
}

constexpr auto get_dist_sqr(const vec2 &lhs, const vec2 &rhs)
{
    return pow2(rhs.x - lhs.x) + pow2(rhs.y - lhs.y);
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<vec2> points;
    points.resize(N);

    for (int n = 0; n < N; ++n)
    {
        cin >> points[n].x >> points[n].y;
    }

    auto cmp_xy = [](const vec2 &lhs, const vec2 &rhs) {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    };

    std::sort(points.begin(), points.end(), cmp_xy);

    coord_t min_square = std::numeric_limits<coord_t>::max();
    coord_t min_dist = (coord_t)sqrt(min_square);
    set<vec2, CompareYX> candidates;
    auto point_it = points.begin();
    for (auto &current : points)
    {
        while (cmp_xy(*point_it, current) && pow2(current.x - point_it->x) >= min_square)
        {
            candidates.erase(*point_it);
            point_it++;
        }

        coord_t min_bound = current.y - min_dist;
        coord_t max_bound = current.y + min_dist;

        auto low_it = candidates.lower_bound({-10001, min_bound});
        auto up_it = candidates.upper_bound({10001, max_bound});

        auto c_it = low_it;
        while (c_it != up_it)
        {
            auto sqr = get_dist_sqr(current, *c_it);
            min_square = std::min(min_square, sqr);
            min_dist = (coord_t)sqrt(min_square);
            ++c_it;
        }

        candidates.insert(current);
    }

    cout << min_square << endl;

    return 0;
}