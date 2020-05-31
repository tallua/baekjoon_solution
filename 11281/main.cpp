#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


size_t N;


struct Tarjan2SAT
{
    vector<vector<size_t>> graph;
    vector<size_t> scc;
    vector<size_t> stack;
    vector<bool> on_stack;
    vector<size_t> topology;
    size_t unique_id;

private:
    size_t N;
    size_t problem_size;

public:
    Tarjan2SAT(size_t N)
    {
        this->N = N;
        this->problem_size = 2 * N + 1;

        graph.resize(problem_size);
    }

    void add(int a, int b)
    {
        graph[inverse(b)].push_back(real(a));
        graph[inverse(a)].push_back(real(b));
    }

    void solve()
    {
        unique_id = 0;
        scc.clear();

        stack.clear();
        on_stack.clear();

        topology.clear();

        scc.resize(problem_size, 0);
        stack.reserve(problem_size);
        on_stack.resize(problem_size, false);

        for (size_t i = 1; i < problem_size; ++i)
        {
            if (scc[i] == 0)
                solve(i);
        }
    }

    bool is_2sat_available()
    {
        for (size_t i = 1; i <= N; ++i)
        {
            if (scc[problem_size - i] == scc[i])
            {
                return false;
            }
        }

        return true;
    }

    vector<bool> get_2sat_example()
    {
        vector<bool> scc_tf;
        vector<bool> visited;
        scc_tf.resize(problem_size, false);
        visited.resize(problem_size, false);
        while (!topology.empty())
        {
            size_t top = topology.back();
            topology.pop_back();

            if (scc_tf[scc[top]] == false)
                fill_scc_false(scc_tf, visited, scc[top], top);
            else
                fill_scc_true(scc_tf, visited, scc[top], top);
        }

        vector<bool> examples;
        examples.resize(N, false);

        for (int i = 0; i < N; ++i)
        {
            examples[i] = scc_tf[scc[i + 1]];
        }

        return examples;
    }

private:

    size_t inverse(int index)
    {
        if (index < 0)
            return static_cast<size_t>(-index);
        return static_cast<size_t>(problem_size - index);
    }

    size_t real(int index)
    {
        if (index < 0)
            return static_cast<size_t>(problem_size + index);
        return static_cast<size_t>(index);
    }

    size_t solve(size_t n)
    {
        scc[n] = ++unique_id;
        stack.push_back(n);
        on_stack[n] = true;

        size_t min_node = scc[n];
        for (size_t adj : graph[n])
        {
            if (scc[adj] == 0)
                min_node = min(min_node, solve(adj));
            else if (on_stack[adj])
                min_node = min(min_node, scc[adj]);
        }

        // create scc
        if (min_node == scc[n])
        {
            size_t scc_id = scc[n];
            while (n != stack.back())
            {
                size_t top = stack.back();
                stack.pop_back();
                on_stack[top] = false;

                scc[top] = scc_id;
            }
            stack.pop_back();
            on_stack[n] = false;

            scc[n] = scc_id;
            topology.push_back(n);
        }

        return min_node;
    }

    void fill_scc_false(vector<bool>& scc_tf, vector<bool>& visited, size_t scc_id, size_t n)
    {
        if (visited[n])
            return;
        visited[n] = true;

        scc_tf[scc[problem_size - n]] = true;

        for (size_t adj : graph[n])
        {
            if (scc[adj] == scc_id)
            {
                fill_scc_false(scc_tf, visited, scc_id, adj);
            }
        }
    }

    void fill_scc_true(vector<bool>& scc_tf, vector<bool>& visited, size_t scc_id, size_t n)
    {
        if (visited[n])
            return;
        visited[n] = true;
        for (size_t adj : graph[n])
        {
            if (scc[adj] == scc_id)
            {
                fill_scc_true(scc_tf, visited, scc_id, adj);
            }
            else
            {
                scc_tf[scc[adj]] = true;
            }
        }
    }
};



int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t M;
    cin >> N >> M;

    Tarjan2SAT tarjan(N);

    for (size_t m = 0; m < M; ++m)
    {
        int a, b;
        cin >> a >> b;

        tarjan.add(a, b);
    }

    tarjan.solve();

    if (tarjan.is_2sat_available())
    {
        cout << "1\n";

        vector<bool> result = tarjan.get_2sat_example();
        for (int n = 0; n < N; ++n)
        {
            cout << result[n] << ' ';
        }
        cout << '\n';
    }
    else
    {
        cout << "0\n";
    }

    cout << endl;

    return 0;
}