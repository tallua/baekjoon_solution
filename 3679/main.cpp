#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct point_t
{
    int x, y;

    constexpr auto const length_square() const noexcept { return (x * x) + (y * y); }
};

constexpr inline point_t operator - (point_t const& lhs, point_t const& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

constexpr auto cross(point_t const& lhs, point_t const& rhs) noexcept {
    return (lhs.x * rhs.y) - (lhs.y * rhs.x);
}

int main(int argc, char** argv)
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t T;
    cin >> T;

    while (T--)
    {
        vector<point_t> const points = []() {
            size_t points_count;
            cin >> points_count;

            vector<point_t> result(points_count);
            for_each(result.begin(), result.end(), [](point_t& point) {
                cin >> point.x >> point.y;
            });

            return result;
        }();

        auto const offset = [&]() {
            auto const min_it = min_element(points.begin(), points.end(), [](auto const& lhs, auto const& rhs) {
                return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
            });
            return points[distance(points.begin(), min_it)];
        }();

        // iota
        vector<size_t> orders(points.size());
        iota(orders.begin(), orders.end(), size_t{});

        // sort by angle and distance from offset
        sort(orders.begin(), orders.end(), [&](auto lhs_index, auto rhs_index) {
            point_t left = points[lhs_index] - offset;
            point_t right = points[rhs_index] - offset;

            auto const cross_val = cross(left, right);
            if (cross_val == 0) {
                return left.length_square() < right.length_square();
            }
            return cross_val > 0;
        });

        // revese order if last elements are aligned
        auto o_rit = orders.rbegin() + 1;
        while (cross(points[*(o_rit - 1)] - offset, points[*o_rit] - offset) == 0) {
            ++o_rit;
        }
        reverse(orders.rbegin(), o_rit);

        // print result
        for_each(orders.begin(), orders.end(), [](auto order) {
            cout << order << ' ';
        });
        cout << '\n';
    }

    return 0;
}
