#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

using coord_t = int;

struct point_t
{
    coord_t x, y;
};

constexpr coord_t distance(const point_t& p1, const point_t& p2)
{
    return (p1.x < p2.x ? p2.x - p1.x : p1.x - p2.x) +
        (p1.y < p2.y ? p2.y - p1.y : p1.y - p2.y);
}

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    vector<point_t> points(N);
    vector<coord_t> x_list(N);
    vector<coord_t> y_list(N);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> points[n].x >> points[n].y;
        x_list[n] = points[n].x;
        y_list[n] = points[n].y;
    }

    sort(x_list.begin(), x_list.end());
    sort(y_list.begin(), y_list.end());

    vector<coord_t> min_distance(N, numeric_limits<coord_t>::max());
    for(size_t x = 0; x < N; ++x)
    {
        for(size_t y = 0; y < N; ++y)
        {
            point_t med = { .x = x_list[x], .y = y_list[y] };
            vector<coord_t> distance_list(N);
            for(size_t n = 0; n < N; ++n)
            {
                distance_list[n] = distance(med, points[n]);
            }

            sort(distance_list.begin(), distance_list.end());

            coord_t dist = 0;
            for(size_t n = 0; n < N; ++n)
            {
                dist += distance_list[n];
                min_distance[n] = min(min_distance[n], dist);
            }
        }
    }

    for(size_t n = 0; n < N; ++n)
    {
        cout << min_distance[n] << ' ';
    }

    return 0;
}


