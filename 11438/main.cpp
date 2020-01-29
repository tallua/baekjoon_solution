#include <iostream>
#include <vector>
#include <array>
#include <iomanip>

using namespace std;
using node_id = int;

template<typename _Type, class _ReduceFn>
class segment_tree
{
public:
    using value_type = _Type;
    using size_type = std::size_t;

private:
    using depth_type = std::size_t;
    using reduce_func_type = _ReduceFn;

private:
    const value_type _default_value;
    const reduce_func_type _reduce_fn;
    std::vector<std::vector<value_type>> _data;

public:
    segment_tree(size_type N,
                 const value_type& default_value = _Type(),
                 const reduce_func_type& reduce_fn = reduce_func_type())
        : _default_value(default_value), _reduce_fn(reduce_fn)
    {
        do
        {
            _data.push_back({});
            _data.back().resize(N, _default_value);

            N = N == 1 ? 0 : (N + 1) >> 1;
        } while (N > 0);
    }

    template <class _ForwardIt>
    segment_tree(_ForwardIt begin, _ForwardIt end,
                 const value_type& default_value = _Type(),
                 const reduce_func_type& reduce_fn = reduce_func_type())
        : _default_value(default_value), _reduce_fn(reduce_fn)
    {
        _data.push_back({});
        _data[0].insert(_data[0].begin(), begin, end);

        size_type N = _data.back().size();
        N = N == 1 ? 0 : (N + 1) >> 1;

        while (N > 0)
        {
            _data.push_back({});
            _data.back().resize(N, _default_value);
            vector<value_type>& prev = _data[_data.size() - 2];

            size_type n = 0;
            while (n < N - 1)
            {
                _data.back()[n] = _reduce_fn(prev[n << 1], prev[(n << 1) + 1]);
                ++n;
            }

            if ((n << 1) + 1 < prev.size())
                _data.back()[n] = _reduce_fn(prev[n << 1], prev[(n << 1) + 1]);
            else
                _data.back()[n] = prev[n << 1];

            N = N == 1 ? 0 : (N + 1) >> 1;
        }
    }

public:
    constexpr size_type size() const
    {
        return _data[0].size();
    }

    value_type& get(size_type index)
    {
        return _data[0].at(index);
    }

    const value_type& get(size_type index) const
    {
        return _data[0].at(index);
    }

    value_type& back()
    {
        return _data[0].back();
    }

    const value_type& back() const
    {
        return _data[0].back();
    }

public:
    void update(size_type index, value_type value)
    {
        if (_data[0].size() <= index)
            return;

        _data[0][index] = value;

        index = index >> 1;
        depth_type depth = 1;
        while (depth < _data.size())
        {
            const auto _child_left = index << 1;
            const auto _child_right = _child_left + 1;

            _data[depth][index] = _data[depth - 1][_child_left];
            if (_child_right < _data[depth - 1].size())
                _data[depth][index] = _reduce_fn(_data[depth][index], _data[depth - 1][_child_right]);

            index = index >> 1;
            depth += 1;
        }
    }

    value_type query_range(size_type begin, size_type end)
    {
        if (end <= begin)
            return _default_value;
        if (_data[0].size() < end)
            return _default_value;

        return _query_range(begin, end - 1, 0);
    }

    template <class _Query>
    size_type index_query(_Query query)
    {
        size_type index = 0;
        depth_type depth = _data.size() - 1;
        while (depth != 0)
        {
            const size_type _child_left = index << 1;
            const size_type _child_right = _child_left + 1;

            if (_data[depth - 1].size() <= _child_right)
            {
                if (query(_data[depth - 1][_child_left], _default_value))
                {
                    return size();
                }
                else
                {
                    index = _child_left;
                }
            }
            else
            {
                if (query(_data[depth - 1][_child_left], _data[depth - 1][_child_right]))
                {
                    index = _child_right;
                }
                else
                {
                    index = _child_left;
                }
            }

            depth--;
        }

        return index;
    }
private:
    /// note : front and back are inclusive range
    value_type _query_range(size_type front, size_type back, depth_type depth)
    {
        if (front == back)
            return _data[depth][front];

        value_type result = _default_value;

        if (front % 2 != 0)
        {
            result = _reduce_fn(result, _data[depth][front]);
            front += 1;
        }

        if (back % 2 == 0)
        {
            result = _reduce_fn(result, _data[depth][back]);
            back -= 1;
        }

        const size_type half_front = front >> 1;
        const size_type half_back = back >> 1;

        if (half_front <= half_back)
            result = _reduce_fn(result, _query_range(half_front, half_back, depth + 1));

        return result;
    }
};

struct min_val
{
    const vector<int> euler_depth;

    min_val(const vector<int>& euler_depth) : euler_depth(euler_depth) { }

    const size_t operator() (const size_t& lhs, const size_t& rhs) const
    {
        if (lhs >= euler_depth.size())
            return rhs;
        if (rhs >= euler_depth.size())
            return lhs;
        return euler_depth[lhs] < euler_depth[rhs] ? lhs : rhs;
    }
};


void build_euler_path(const vector<vector<node_id>>& edges, node_id parent,
    vector<node_id>& path, vector<int>& depth, vector<size_t>& first, vector<size_t>& last)
{
    node_id cur_node = path.back();
    int cur_depth = depth.back();

    first[cur_node] = path.size() - 1;
    for (const node_id& child : edges[cur_node])
    {
        if (child != parent)
        {
            path.push_back(child);
            depth.push_back(cur_depth + 1);
            build_euler_path(edges, cur_node, path, depth, first, last);
            path.push_back(cur_node);
            depth.push_back(cur_depth);
        }
    }
    last[cur_node] = path.size() - 1;
}


int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<vector<node_id>> edges;
    edges.resize(N);

    for (int n = 0; n < N - 1; ++n)
    {
        int a, b;
        cin >> a >> b;

        edges[a - 1].push_back(b - 1);
        edges[b - 1].push_back(a - 1);
    }

    // build euler_path
    vector<size_t> first_appear;
    vector<size_t> last_appear;
    first_appear.resize(N);
    last_appear.resize(N);

    vector<node_id> euler_path;
    vector<int> euler_depth;
    euler_path.reserve(2 * N - 1);
    euler_depth.reserve(2 * N - 1);

    euler_path.push_back(0);
    euler_depth.push_back(0);

    build_euler_path(edges, 0, euler_path, euler_depth, first_appear, last_appear);

    //for (int i = 0; i < euler_path.size(); ++i)
    //{
    //    cout << setw(2) << i << ' ';
    //}
    //cout << endl;
    //for (int i = 0; i < euler_path.size(); ++i)
    //{
    //    cout << setw(2) << euler_path[i] << ' ';
    //}
    //cout << endl;
    //for (int i = 0; i < euler_depth.size(); ++i)
    //{
    //    cout << setw(2) << euler_depth[i] << ' ';
    //}
    //cout << endl;

    // build cache
    vector<size_t> indexes;
    indexes.resize(2 * N - 1);
    for (int i = 0; i < indexes.size(); ++i)
    {
        indexes[i] = i;
    }
    min_val reduce_fn(euler_depth);
    segment_tree<size_t, min_val> segtree(indexes.begin(), indexes.end(), euler_depth.size(), reduce_fn);

    int M;
    cin >> M;

    while (M--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        auto a_indx = first_appear[a];
        auto b_indx = first_appear[b];

        if (b_indx < a_indx)
            swap(a_indx, b_indx);

        auto result = segtree.query_range(a_indx, b_indx + 1);

        cout << (euler_path[result] + 1) << '\n';
    }

    return 0;
}