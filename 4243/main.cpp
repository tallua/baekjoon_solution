#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <limits>

using namespace std;
using ull = unsigned long long;

struct task_t
{
    size_t left, current, right;

    bool operator<(const task_t &other) const
    {
        return this->left == other.left ? this->current < other.current : this->left < other.left;
    }
};

int main(int argc, char **argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        size_t start;
        cin >> start;
        start--;

        vector<ull> dist_arr;
        dist_arr.resize(N - 1);
        for (size_t i = 0; i < N - 1; ++i)
        {
            cin >> dist_arr[i];
        }

        vector<vector<ull>> dist_map;
        dist_map.resize(N);
        for (size_t i = 0; i < N; ++i)
        {
            dist_map[i].resize(N);
            dist_map[i][i] = 0;

            if (i != 0)
                dist_map[i - 1][i] = dist_arr[i - 1];
            if (i != N - 1)
                dist_map[i][i + 1] = dist_arr[i];
        }

        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < i; ++j)
            {
                dist_map[i][j] = dist_map[j][i];
            }

            for (size_t j = i + 1; j < N; ++j)
            {
                dist_map[i][j] = dist_map[i][j - 1] + dist_map[j - 1][j];
            }
        }

        map<task_t, ull> current_tasks;
        map<task_t, ull> next_tasks;
        current_tasks.insert(make_pair<task_t, ull>({start, start, start}, 0));
        for (size_t i = 0; i < N - 1; ++i)
        {
            for (const auto &task : current_tasks)
            {
                const task_t &cur = task.first;

                if (cur.left > 0)
                {
                    task_t next = {cur.left - 1, cur.left - 1, cur.right};
                    ull cost = task.second + (N - 1 - (cur.right - cur.left)) * dist_map[cur.left - 1][cur.current];

                    auto n_it = next_tasks.find(next);
                    if (n_it == next_tasks.end())
                        next_tasks.insert(make_pair(next, cost));
                    else if (cost < n_it->second)
                        next_tasks.at(next) = cost;
                }

                if (cur.right < N - 1)
                {
                    task_t next = {cur.left, cur.right + 1, cur.right + 1};
                    ull cost = task.second + (N - 1 - (cur.right - cur.left)) * dist_map[cur.current][cur.right + 1];

                    auto n_it = next_tasks.find(next);
                    if (n_it == next_tasks.end())
                        next_tasks.insert(make_pair(next, cost));
                    else if (cost < n_it->second)
                        next_tasks.at(next) = cost;
                }
            }

            current_tasks.clear();
            std::swap(next_tasks, current_tasks);
        }

        ull min_cost = numeric_limits<ull>::max();
        for (auto &t : current_tasks)
        {
            min_cost = min(min_cost, t.second);
        }

        cout << min_cost << '\n';
    }

    return 0;
}