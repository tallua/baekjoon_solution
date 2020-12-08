#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

using coord_t = size_t;
struct point_t
{
    coord_t x, y;
};

coord_t dist(const point_t& lhs, const point_t& rhs)
{
    return
        (lhs.x < rhs.x ? rhs.x - lhs.x : lhs.x - rhs.x) +
        (lhs.y < rhs.y ? rhs.y - lhs.y : lhs.y - rhs.y);
}

using car_id_t = size_t;
struct report_t
{
    size_t moved_from;
    coord_t moved_distance;
    bool car1;
};

void print_report(const vector<report_t>& reports, size_t N)
{
    for(size_t i = { 0 }; i < N; ++i)
    {
        cout << reports[i].moved_from << "/" << reports[i].moved_distance << "/" << reports[i].car1 << " ";
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    coord_t N;
    cin >> N;

    size_t case_count;
    cin >> case_count;

    const size_t point_counts = case_count + 2;
    vector<point_t> case_points(point_counts);
    case_points[0] = { .x = 1, .y = 1 };
    case_points[1] = { .x = N, .y = N };
    for(size_t i = { 2 }; i < point_counts; ++i)
    {
        cin >> case_points[i].x >> case_points[i].y;
    }

    vector<report_t> reports(point_counts - 1);
    reports[0] = { .moved_from = 0, .moved_distance = dist(case_points[1], case_points[2]), .car1 = false};
    reports[1] = { .moved_from = 1, .moved_distance = dist(case_points[0], case_points[2]), .car1 = true};
    //print_report(reports, 2);
    for(size_t current = { 3 }; current < point_counts; ++current)
    {
        const coord_t moved_distance = dist(case_points[current - 1], case_points[current]);
        report_t shortest_report { .moved_distance = numeric_limits<coord_t>::max() };
        for(size_t prev = { 0 }; prev < current - 1; ++prev)
        {
            coord_t distance = reports[prev].moved_distance + dist(case_points[prev], case_points[current]);
            if(distance < shortest_report.moved_distance)
            {
                shortest_report = { .moved_from = prev, .moved_distance = distance, .car1 = !reports[prev].car1 };
            }
            reports[prev].moved_distance += moved_distance;
        }
        reports[current - 1] = shortest_report;

        //print_report(reports, current);
    }
    
    // backtrace
    size_t min_report = 0;
    for(size_t i = { 1 }; i < point_counts - 1; ++i)
    {
        if(reports[i].moved_distance < reports[min_report].moved_distance)
            min_report = i;
    }

    size_t backtrace_current = min_report;
    vector<size_t> backtrace;
    backtrace.reserve(case_count);
    while(backtrace.size() != case_count) {
        backtrace.push_back(reports[backtrace_current].car1 ? 1 : 2);
        if(backtrace_current + backtrace.size() == case_count + 1)
            backtrace_current = reports[backtrace_current].moved_from;
    }

    cout << reports[min_report].moved_distance << '\n';
    while(!backtrace.empty()) {
        size_t cur = backtrace.back();
        backtrace.pop_back();
        cout << cur << '\n';
    }

    return 0;
}