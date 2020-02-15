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
    coord_t x, y;
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
    set<coord_t> x_coord_set;
    set<coord_t> y_coord_set;
    for (size_t n = 0; n < departs.size(); ++n)
    {
        cin >> departs[n].lx >> departs[n].ly >> departs[n].hx >> departs[n].hy >> departs[n].cost;
    }

    for (const auto& depart : departs)
    {
        x_coord_set.insert(depart.lx);
        x_coord_set.insert(depart.hx);
        y_coord_set.insert(depart.ly);
        y_coord_set.insert(depart.hy);
    }

    x_coord_set.insert(a);
    y_coord_set.insert(b);
    x_coord_set.insert(c);
    y_coord_set.insert(d);
    x_coord_set.insert(0);
    y_coord_set.insert(0);
    x_coord_set.insert(100000000);
    y_coord_set.insert(100000000);

    indx_to_x.reserve(x_coord_set.size());
    indx_to_y.reserve(y_coord_set.size());

    for (const auto& x_val : x_coord_set)
        indx_to_x.push_back(x_val);
    for (const auto& y_val : y_coord_set)
        indx_to_y.push_back(y_val);
}

int main(int argc, char** argv)
{
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

    vector<vector<cost_t>> horz_costs;
    horz_costs.resize(grid_y_size);
    for (auto& r : horz_costs)
        r.resize(grid_x_size - 1, 10);
    vector<vector<cost_t>> vert_costs;
    vert_costs.resize(grid_y_size - 1);
    for (auto& r : vert_costs)
        r.resize(grid_x_size, 10);

    for (const auto& rect : departs)
    {
        const size_t lx = x_to_indx[rect.lx];
        const size_t ly = y_to_indx[rect.ly];
        const size_t hx = x_to_indx[rect.hx];
        const size_t hy = y_to_indx[rect.hy];

        for (size_t y = ly + 1; y < hy; ++y)
        {
            for (size_t x = lx; x < hx; ++x)
            {
                horz_costs[y][x] = rect.cost;
            }
        }

        for (size_t x = lx + 1; x < hx; ++x)
        {
            for (size_t y = ly; y < hy; ++y)
            {
                vert_costs[y][x] = rect.cost;
            }
        }
    }

    // values for simulate
    vector<bool> visited;
    visited.resize(grid_y_size * grid_x_size, false);

    auto dist_to_end = [&](coord_t x, coord_t y) -> cost_t {
        return (abs((cost_t)end_x - x) + abs((cost_t)end_y - y)) * 10;
    };

    // a* with priority queue
    priority_queue<astar_task, vector<astar_task>, task_sort> pq;
    pq.push({ start_x, start_y, 0LL, dist_to_end(start_x, start_y) });

    cost_t result = 0;
    while (true)
    {
        const astar_task task = pq.top();
        pq.pop();
        //cout << "mark : " << task.x << " " << task.y << 
        //    " : " << task.actual << " | " << task.estimate << endl;
        if (task.x == end_x && task.y == end_y)
        {
            result = task.actual;
            break;
        }

        const size_t cur_x = x_to_indx[task.x];
        const size_t cur_y = y_to_indx[task.y];

        if (visited[calc_indx(cur_y, cur_x)])
            continue;
        visited[calc_indx(cur_y, cur_x)] = true;

        // up
        if (cur_y != grid_y_size - 1 && !visited[calc_indx(cur_y + 1, cur_x)])
        {
            coord_t next_x = task.x;
            coord_t next_y = indx_to_y[cur_y + 1];
            cost_t actual = task.actual + vert_costs[cur_y][cur_x] * abs(next_y - task.y);
            pq.push({ next_x, next_y, actual, actual + dist_to_end(next_x, next_y) });
        }
        // down
        if (cur_y != 0 && !visited[calc_indx(cur_y - 1, cur_x)])
        {
            coord_t next_x = task.x;
            coord_t next_y = indx_to_y[cur_y - 1];
            cost_t actual = task.actual + vert_costs[cur_y - 1][cur_x] * abs(next_y - task.y);
            pq.push({ next_x, next_y, actual, actual + dist_to_end(next_x, next_y) });
        }
        // right
        if (cur_x != grid_x_size - 1 && !visited[calc_indx(cur_y, cur_x + 1)])
        {
            coord_t next_x = indx_to_x[cur_x + 1];
            coord_t next_y = task.y;
            cost_t actual = task.actual + horz_costs[cur_y][cur_x] * abs(next_x - task.x);
            pq.push({ next_x, next_y, actual, actual + dist_to_end(next_x, next_y) });
        }
        // left
        if (cur_x != 0 && !visited[calc_indx(cur_y, cur_x - 1)])
        {
            coord_t next_x = indx_to_x[cur_x - 1];
            coord_t next_y = task.y;
            cost_t actual = task.actual + horz_costs[cur_y][cur_x - 1] * abs(next_x - task.x);
            pq.push({ next_x, next_y, actual, actual + dist_to_end(next_x, next_y) });
        }
    }

    cout << result << endl;

    return 0;
}