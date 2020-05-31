#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


size_t N;


struct Tarjan2SAT
{
    vector<vector<size_t>> graph;
    vector<size_t> scc;
    vector<size_t> stack;
    vector<bool> on_stack;
    size_t cnt;

private:
    size_t N;
    size_t N2;
    size_t problem_size;

public:
    Tarjan2SAT(size_t N)
    {
        this->N = N;
        this->N2 = N * 2;
        this->problem_size = 2 * N + 1;

        graph.resize(problem_size);
    }

    void add(int a, int b)
    {
        graph[inverse(b)].push_back(real(a));
        graph[inverse(a)].push_back(real(b));
    }

    bool is_2sat_available()
    {
        solve();

        for(size_t i = 1; i <= N; ++i)
        {
            if(scc[problem_size - i] == scc[i])
            {
                return false;
            }
        }

        return true;
    }

private:

    size_t inverse(int index)
    {
        if(index < 0)
            return static_cast<size_t>(-index);
        return static_cast<size_t>(problem_size - index);
    }

    size_t real(int index)
    {
        if(index < 0)
            return static_cast<size_t>(problem_size + index);
        return static_cast<size_t>(index);
    }

    void solve()
    {
        scc.clear();
        stack.clear();
        on_stack.clear();
        cnt = 0;

        scc.resize(problem_size, 0);
        stack.reserve(problem_size);
        on_stack.resize(problem_size, false);

        for(size_t i = 1; i < problem_size; ++i)
        {
            if(scc[i] == 0)
                solve(i);
        }
    }

    size_t solve(size_t n)
    {
        scc[n] = cnt++;
        stack.push_back(n);
        on_stack[n] = true;

        size_t min_node = scc[n];
        for(size_t adj : graph[n])
        {
            if(scc[adj] == 0)
                min_node = min(min_node, solve(adj));
            else if(on_stack[adj])
                min_node = min(min_node, scc[adj]);
        }

        if(min_node == scc[n])
        {
            while(n != stack.back())
            {
                size_t top = stack.back();
                stack.pop_back();
                on_stack[top] = false;

                scc[top] = scc[n];
            }
            on_stack[n] = false;
            stack.pop_back();
        }

        return min_node;
    }
};



int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    size_t M;
    cin >> N >> M;

    Tarjan2SAT tarjan(N);
    
    for(size_t m = 0; m < M; ++m)
    {
        int a, b;
        cin >> a >> b;

        tarjan.add(a, b);
    }

    cout << tarjan.is_2sat_available() << endl;

    return 0;
}