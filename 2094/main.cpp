#include <iostream>
#include <map>
#include <vector>
#include <array>

using namespace std;

template <typename T, size_t SZ, class Reducer, T default_val>
class fixed_segtree
{
private:
    Reducer reducer;
    size_t N = 0;
    std::array<T, SZ * 4> data;

public:

    fixed_segtree() = default;
    fixed_segtree(const vector<T>& data)
        : N(data.size())
    {
        if(N != 0)
            _build(data, 0u, 0u, N);
    }

    void build(const vector<T>& data)
    {
        N = data.size();
        if(N != 0)
            _build(data, 0u, 0u, N);
    }

    T query(size_t begin, size_t end) const
    {
        if(end <= begin || N < end)
            return default_val;
        return _query(begin, end, 0u, 0u, N);
    }

private:
    void _build(const vector<T>& d, size_t index, size_t begin, size_t end)
    {
        if(end - begin <= 1) {
            data[index] = d[begin];
            return;
        }

        size_t mid = (begin + end) / 2;
        _build(d, index * 2 + 1, begin, mid);
        _build(d, index * 2 + 2, mid, end);

        data[index] = reducer(data[index * 2 + 1], data[index * 2 + 2]);
    }

    T _query(size_t range_begin, size_t range_end, size_t index, size_t begin, size_t end) const
    {
        if(range_end <= begin || end <= range_begin)
            return default_val;
        if(range_begin <= begin && end <= range_end)
            return data[index];

        size_t mid = (begin + end) / 2;
        return reducer(
            _query(range_begin, range_end, index * 2 + 2, mid, end),
            _query(range_begin, range_end, index * 2 + 1, begin, mid));
    }
};

template <typename T>
size_t bisearch(const vector<T>& arr, const T target, size_t begin, size_t end)
{
    while(end - begin > 1)
    {
        size_t mid = (begin + end) / 2;
        if (target < arr[mid])
            end = mid;
        else
            begin = mid;
    }

    return target <= arr[begin] ? begin : end;
}

using precipitation_t = int32_t;
using year_t = int32_t;


struct max_preci
{
    constexpr precipitation_t operator() (precipitation_t lhs, precipitation_t rhs) const
    {
        return lhs < rhs ? rhs : lhs;
    }
};

struct bool_and
{
    constexpr  bool operator() (bool lhs, bool rhs) const
    {
        return lhs && rhs;
    }
};

using preci_segtree_t = fixed_segtree<precipitation_t, 50000, max_preci, precipitation_t(0)>;
preci_segtree_t preci_segtree;
using continuous_segtree_t = fixed_segtree<bool, 50000, bool_and, true>;
continuous_segtree_t continuous_segtree;

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    vector<year_t> years(N);
    vector<precipitation_t> precis(N);
    vector<bool> year_adj(N - 1);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> years[n] >> precis[n];
        if(n != 0)
        {
            year_adj[n - 1] = ((years[n] - years[n - 1]) == year_t(1));
        }
    }

    preci_segtree.build(precis);
    continuous_segtree.build(year_adj);

    size_t M;
    cin >> M;
    while(M--)
    {
        year_t from, to;
        cin >> from >> to;

        size_t gap_begin = bisearch(years, from, 0u, N);
        size_t gap_end = bisearch(years, to, 0u, N);

        const size_t from_index = gap_begin;
        const size_t to_index = gap_end;

        bool from_found = gap_begin != N && years[gap_begin] == from;
        bool to_found = gap_end != N && years[gap_end] == to;

        if(from_found)
            gap_begin++;

        if(!from_found && !to_found)
        {
            cout << "maybe\n";
            continue;
        }

        auto biggest = preci_segtree.query(gap_begin, gap_end);
        if(!from_found)
        {
            cout << (biggest < precis[to_index] ? "maybe\n" : "false\n");
            continue;
        }

        if(!to_found)
        {
            cout << (biggest < precis[from_index] ? "maybe\n" : "false\n");
            continue;
        }

        bool is_continuous = continuous_segtree.query(from_index, to_index);
        bool is_ordered = (precis[from_index] >= precis[to_index]) && (biggest < precis[to_index]);
        if(!is_ordered)
        {
            cout << "false\n";
            continue;
        }

        cout << (is_continuous ? "true\n" : "maybe\n");
    }

    return 0;
}