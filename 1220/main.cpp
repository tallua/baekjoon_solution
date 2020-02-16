#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

using coord_t = int;
using cost_t = long long;

struct rect_t
{
    int lx, ly, hx, hy;
    int cost;
};

struct astar_task
{
    size_t x, y;
    cost_t actual;
    cost_t estimate;

};

struct task_sort
{
    bool operator() (const astar_task& lhs, const astar_task& rhs)
    {
        return lhs.estimate > rhs.estimate;
    }
};

void parse_inputs(vector<rect_t>& departs, vector<coord_t>& indx_to_x, vector<coord_t>& indx_to_y,
                  coord_t a, coord_t b, coord_t c, coord_t d)
{
    for (size_t n = 0; n < departs.size(); ++n)
    {
        cin >> departs[n].lx >> departs[n].ly >> departs[n].hx >> departs[n].hy >> departs[n].cost;
    }

    vector<coord_t> x_coord_set;
    x_coord_set.reserve(departs.size() + 2);
    vector<coord_t> y_coord_set;
    y_coord_set.reserve(departs.size() + 2);
    for (const auto& depart : departs)
    {
        x_coord_set.push_back(depart.lx);
        x_coord_set.push_back(depart.hx);
        y_coord_set.push_back(depart.ly);
        y_coord_set.push_back(depart.hy);
    }

    x_coord_set.push_back(a);
    y_coord_set.push_back(b);
    x_coord_set.push_back(c);
    y_coord_set.push_back(d);
    x_coord_set.push_back(100000000);
    y_coord_set.push_back(100000000);

    sort(x_coord_set.begin(), x_coord_set.end());
    sort(y_coord_set.begin(), y_coord_set.end());

    indx_to_x.reserve(x_coord_set.size());
    indx_to_y.reserve(y_coord_set.size());
    indx_to_x.push_back(0);
    indx_to_y.push_back(0);

    for (const auto& x_val : x_coord_set)
    {
        if (indx_to_x.back() != x_val)
            indx_to_x.push_back(x_val);
    }
    for (const auto& y_val : y_coord_set)
    {
        if (indx_to_y.back() != y_val)
            indx_to_y.push_back(y_val);
    }
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    coord_t start_x, start_y, end_x, end_y;
    cin >> start_x >> start_y >> end_x >> end_y;

    size_t N;
    cin >> N;

    vector<rect_t> departs;
    vector<coord_t> indx_to_x;
    vector<coord_t> indx_to_y;
    departs.resize(N);
    parse_inputs(departs, indx_to_x, indx_to_y, start_x, start_y, end_x, end_y);

    const size_t max_grid_size = 2004;
    const size_t grid_x_size = indx_to_x.size();
    const size_t grid_y_size = indx_to_y.size();
    unordered_map<coord_t, size_t> x_to_indx;
    for (size_t x = 0; x < indx_to_x.size(); ++x)
    {
        x_to_indx[indx_to_x[x]] = x;
    }
    unordered_map<coord_t, size_t> y_to_indx;
    for (size_t y = 0; y < indx_to_y.size(); ++y)
    {
        y_to_indx[indx_to_y[y]] = y;
    }

    // build cost_map using line
    auto calc_indx = [&](size_t y, size_t x)
    {
        return y * grid_x_size + x;
    };

    vector<cost_t> horz_costs;
    horz_costs.resize(grid_y_size * grid_x_size, 10);
    vector<cost_t> vert_costs;
    vert_costs.resize(grid_y_size * grid_x_size, 10);

    for (const auto& rect : departs)
    {
        const size_t& lx = x_to_indx[rect.lx];
        const size_t& ly = y_to_indx[rect.ly];
        const size_t& hx = x_to_indx[rect.hx];
        const size_t& hy = y_to_indx[rect.hy];

        for (size_t y = ly + 1; y < hy; ++y)
        {
            for (size_t x = lx; x < hx; ++x)
            {
                horz_costs[calc_indx(y, x)] = rect.cost;
            }
        }

        for (size_t x = lx + 1; x < hx; ++x)
        {
            for (size_t y = ly; y < hy; ++y)
            {
                vert_costs[calc_indx(y, x)] = rect.cost;
            }
        }
    }

    // values for simulate
    vector<bool> visited;
    visited.resize(grid_y_size * grid_x_size, false);

    auto cost_to_end = [&](const size_t& x, const size_t& y) -> cost_t {
        return (abs(end_x - indx_to_x[x]) + abs(end_y - indx_to_y[y])) * 10;
    };

    // a* with priority queue
    const size_t start_indx_x = x_to_indx[start_x];
    const size_t start_indx_y = y_to_indx[start_y];
    const size_t end_indx_x = x_to_indx[end_x];
    const size_t end_indx_y = y_to_indx[end_y];
    priority_queue<astar_task, vector<astar_task>, task_sort> pq;
    pq.push({ start_indx_x, start_indx_y, 0LL, cost_to_end(start_indx_x, start_indx_y) });

    cost_t result = 0;
    while (true)
    {
        const astar_task task = pq.top();
        pq.pop();
        //cout << "mark : " << task.x << " " << task.y << 
        //    " : " << task.actual << " | " << task.estimate << endl;
        if (task.x == end_indx_x && task.y == end_indx_y)
        {
            result = task.actual;
            break;
        }

        if (visited[calc_indx(task.y, task.x)])
            continue;
        visited[calc_indx(task.y, task.x)] = true;

        // up
        if (task.y != grid_y_size - 1 && !visited[calc_indx(task.y + 1, task.x)])
        {
            const size_t next_x = task.x;
            const size_t next_y = task.y + 1;
            const cost_t cost = vert_costs[calc_indx(task.y, task.x)];
            const coord_t dist = abs(indx_to_y[next_y] - indx_to_y[task.y]);
            const cost_t actual = task.actual + cost * dist;
            pq.push({ next_x, next_y, actual, actual + cost_to_end(next_x, next_y) });
        }
        // down
        if (task.y != 0 && !visited[calc_indx(task.y - 1, task.x)])
        {
            const size_t next_x = task.x;
            const size_t next_y = task.y - 1;
            const cost_t cost = vert_costs[calc_indx(task.y - 1, task.x)];
            const coord_t dist = abs(indx_to_y[next_y] - indx_to_y[task.y]);
            const cost_t actual = task.actual + cost * dist;
            pq.push({ next_x, next_y, actual, actual + cost_to_end(next_x, next_y) });
        }
        // right
        if (task.x != grid_x_size - 1 && !visited[calc_indx(task.y, task.x + 1)])
        {
            const size_t next_x = task.x + 1;
            const size_t next_y = task.y;
            const cost_t cost = horz_costs[calc_indx(task.y, task.x)];
            const coord_t dist = abs(indx_to_x[next_x] - indx_to_x[task.x]);
            const cost_t actual = task.actual + cost * dist;
            pq.push({ next_x, next_y, actual, actual + cost_to_end(next_x, next_y) });
        }
        // left
        if (task.x != 0 && !visited[calc_indx(task.y, task.x - 1)])
        {
            const size_t next_x = task.x - 1;
            const size_t next_y = task.y;
            const cost_t cost = horz_costs[calc_indx(task.y, task.x - 1)];
            const coord_t dist = abs(indx_to_x[next_x] - indx_to_x[task.x]);
            const cost_t actual = task.actual + cost * dist;
            pq.push({ next_x, next_y, actual, actual + cost_to_end(next_x, next_y) });
        }
    }

    cout << result << endl;

    return 0;
}