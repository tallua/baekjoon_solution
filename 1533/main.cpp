#include <iostream>
#include <map>
#include <array>
#include <vector>

using namespace std;

using times_t = int;
using count_t = unsigned long long;
using graph_t = vector<vector<times_t>>;

const count_t mod_num = 1000003ull;

struct count_graph_t
{
    size_t N;
    vector<count_t> counts;

    count_graph_t(const graph_t& graph): 
        N(graph.size()),
        counts(25 * graph.size() * graph.size(), 0ull)
    {
        const size_t N5 = N * 5;
        for(size_t from = 0; from < N; ++from)
        {
            for(size_t to = 0; to < N; ++to)
            {
                if(graph[from][to] != 0) 
                {
                    const size_t from_index = from * 5;
                    const size_t to_index = to * 5 + graph[from][to] - 1;
                    counts[from_index * N5 + to_index] = 1;
                }
            }
        }

        for(size_t from = 0; from < N; ++from)
        {
            for(size_t i = 1; i < 5; ++i)
            {
                    const size_t from_index = from * 5 + i;
                    const size_t to_index = from * 5 + i - 1;
                    counts[from_index * N5 + to_index] = 1;
            }
        }
    }

    count_graph_t operator * (const count_graph_t& other) const
    {
        count_graph_t result(*this);
        result *= other;

        return result;
    }

    count_graph_t& operator *= (const count_graph_t& other)
    {
        const size_t N5 = 5 * N;
        vector<count_t> result(N5 * N5);
        for(size_t from = 0; from < N5; ++from)
        {
            for(size_t to = 0; to < N5; ++to)
            {
                result[from * N5 + to] = 0;
                for(size_t mid = 0; mid < N5; ++mid)
                {
                    const count_t next = this->counts[from * N5 + mid] * other.counts[mid * N5 + to];
                    result[from * N5 + to] += next;
                }
                result[from * N5 + to] %= mod_num;
            }
        }

        std::swap(this->counts, result);

        return *this;
    }
    
    count_t count(size_t from, size_t to) const
    {
        return counts[from * 25 * N + to * 5];
    }

    void print() const
    {
        for(size_t from = 0; from < N * 5; ++from)
        {
            for(size_t to = 0; to < N * 5; ++to)
            {
                cout << counts[from * 5 * N + to] << ' ';
            }

            cout << endl;
        }
        cout << endl;
    }
};

count_graph_t calc(times_t time, const count_graph_t& graph)
{
    if(time == 1) 
    {
        return graph;
    }

    const times_t half_time = time / 2;
    auto half = calc(half_time, graph);
    auto result = half * half;
    if(time % 2 == 1) 
    {
        result *= graph;
    }

    return result;
}

graph_t parse_input(size_t N)
{
    graph_t graph;
    graph.resize(N);
    for(size_t from = 0; from < N; ++from)
    {
        graph[from].resize(N);
        for(size_t to = 0; to < N; ++to)
        {
            char tmp;
            cin >> tmp;
            graph[from][to] = tmp - '0';
        }
    }

    return graph;
}

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N;
    size_t start, end;
    times_t target;
    cin >> N >> start >> end >> target;

    const auto graph = parse_input(N);
    const count_graph_t count_graph(graph);
    const auto result = calc(target, count_graph);

    cout << result.count(start - 1, end - 1) << '\n';

    return 0;
}