#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;
using flow_t = int;


struct DinicGraph
{
    using level_t = int;

    const size_t _N;

    vector<vector<flow_t>> _current_flow;
    vector<vector<flow_t>> _maximum_flow;

    DinicGraph(size_t N)
        : _N(N)
    {
        _current_flow.resize(N);
        for(size_t n = 0; n < N; ++n)
            _current_flow[n].resize(N, 0);

        _maximum_flow.resize(N);
        for(size_t n = 0; n < N; ++n)
            _maximum_flow[n].resize(N, 0);
    }

    void set_max_flow(size_t s, size_t t, flow_t max_flow)
    {
        _maximum_flow[s][t] = max_flow;
    }

    void add_max_flow(size_t s, size_t t, flow_t max_flow)
    {
        _maximum_flow[s][t] += max_flow;
    }

    void clear()
    {
        for(size_t n1 = 0; n1 < _N; ++n1)
        {
            for(size_t n2 = 0; n2 < _N; ++n2)
            {
                _current_flow[n1][n2] = 0;
            }
        }
    }

    flow_t dfs(const vector<level_t>& level, size_t s, size_t t, flow_t cap)
    {
        if(s == t)
            return cap;
        if(cap <= 0)
            return 0;

        flow_t orig_cap = cap;
        level_t next_level = level[s] + 1;
        for(size_t n = 0; n < _N; ++n)
        {
            if(next_level == level[n] && _maximum_flow[s][n] - _current_flow[s][n] > 0)
            {
                flow_t tmp = dfs(level, n, t, min(cap, _maximum_flow[s][n] - _current_flow[s][n]));
                if(tmp > 0)
                {
                    _current_flow[s][n] += tmp;
                    _current_flow[n][s] -= tmp;
                    cap -= tmp;
                }
            }
        }

        return orig_cap - cap;
    }

    bool step(size_t s, size_t t)
    {
        vector<level_t> level_graph;
        level_graph.resize(_N, -1);
        level_graph[s] = 0;

        queue<size_t> q;
        q.push(s);

        // V^2
        while(!q.empty())
        {
            size_t ns = q.front();
            q.pop();

            for(size_t nt = 0; nt < _N; ++nt)
            {
                if(level_graph[nt] == -1 && _maximum_flow[ns][nt] - _current_flow[ns][nt] > 0)
                {
                    level_graph[nt] = level_graph[ns] + 1;
                    q.push(nt);
                }
            }
        }

        //cout << "level : ";
        //for(const auto& l : level_graph)
        //{
        //    cout << l << ' ';
        //}
        //cout << endl;

        if(level_graph[t] == -1)
            return false;

        flow_t add = dfs(level_graph, s, t, numeric_limits<flow_t>::max());
        //cout << "flow added : " << add << endl;
        if(add > 0)
            return true;
        return false;
    }

    flow_t flow(size_t s, size_t t)
    {
        while(step(s, t))
        {

        }

        flow_t flow_sum = 0;
        for(size_t n = 0; n < _N; ++n)
        {
            if(0 < _current_flow[s][n])
                flow_sum += _current_flow[s][n];
        }

        return flow_sum;
    }
};




int main(int argc, char** argv)
{
    DinicGraph graph(52);

    int N;
    cin >> N;

    for(size_t n = 0; n < N; ++n)
    {
        char a, b;
        flow_t max_flow;

        cin >> a >> b >> max_flow;

        size_t node_a = 'A' <= a && a <= 'Z' ? a - 'A' : a - 'a' + 26;
        size_t node_b = 'A' <= b && b <= 'Z' ? b - 'A' : b - 'a' + 26;
        graph.add_max_flow(node_a, node_b, max_flow);
        graph.add_max_flow(node_b, node_a, max_flow);
    }

    flow_t result = graph.flow('A' - 'A', 'Z' - 'A');
    cout << result << endl;

    return 0;
}
