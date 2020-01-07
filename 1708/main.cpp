#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point_t
{
    long long x, y;
};

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<point_t> points;
    points.resize(N);

    for (int n = 0; n < N; ++n)
    {
        cin >> points[n].x >> points[n].y;
    }

    sort(points.begin(), points.end(), [](const auto &p1, const auto &p2) {
        if (p1.x < p2.x)
            return true;
        else if (p1.x > p2.x)
            return false;
        return p1.y < p2.y;
    });

    vector<size_t> upper_hull;
    upper_hull.push_back(0);

    for (int i = 1; i < N; ++i)
    {
        const auto &cur = points[i];

        while (upper_hull.size() >= 2)
        {
            const auto &p0 = points[upper_hull[upper_hull.size() - 2]];
            const auto &p1 = points[upper_hull[upper_hull.size() - 1]];

            const point_t v_prev = {p1.x - p0.x, p1.y - p0.y};
            const point_t v_cur = {cur.x - p0.x, cur.y - p0.y};

            const auto det = v_prev.x * v_cur.y - v_prev.y * v_cur.x;

            if (det <= 0)
            {
                upper_hull.pop_back();
            }
            else
            {
                break;
            }
        }

        upper_hull.push_back(i);
    }

    vector<size_t> lower_hull;
    lower_hull.push_back(N - 1);

    for (int i = N - 2; i >= 0; --i)
    {
        const auto &cur = points[i];

        while (lower_hull.size() >= 2)
        {
            const auto &p0 = points[lower_hull[lower_hull.size() - 2]];
            const auto &p1 = points[lower_hull[lower_hull.size() - 1]];

            const point_t v_prev = {p1.x - p0.x, p1.y - p0.y};
            const point_t v_cur = {cur.x - p0.x, cur.y - p0.y};

            const auto det = v_prev.x * v_cur.y - v_prev.y * v_cur.x;

            if (det <= 0)
            {
                lower_hull.pop_back();
            }
            else
            {
                break;
            }
        }

        lower_hull.push_back(i);
    }

    cout << (upper_hull.size() + lower_hull.size() - 2) << endl;

    return 0;
}