#include <iostream>
#include <vector>

using namespace std;

template <typename _Type, class _ReduceFn>
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
    const reduce_func_type _reduce_fn = reduce_func_type();
    std::vector<std::vector<value_type>> _data;

public:
    segment_tree(size_type N,
                 const value_type &default_value = _Type())
        : _default_value(default_value)
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
                 const value_type &default_value = _Type())
        : _default_value(default_value)
    {
        _data.push_back({});
        _data[0].insert(_data[0].begin(), begin, end);

        size_type N = _data.back().size();
        N = N == 1 ? 0 : (N + 1) >> 1;

        while (N > 0)
        {
            _data.push_back({});
            _data.back().resize(N, _default_value);
            vector<value_type> &prev = _data[_data.size() - 2];

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

    value_type &get(size_type index)
    {
        return _data[0].at(index);
    }

    const value_type &get(size_type index) const
    {
        return _data[0].at(index);
    }

    value_type &back()
    {
        return _data[0].back();
    }

    const value_type &back() const
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

using sign = int;

template <typename _Type>
struct mult
{
};

template <>
struct mult<sign>
{
    const sign operator()(const sign &lhs, const sign &rhs) const
    {
        return lhs * rhs;
    }
};

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K;
    while (cin >> N >> K)
    {
        vector<sign> signs;
        signs.resize(N);
        for (int n = 0; n < N; ++n)
        {
            cin >> signs[n];
            signs[n] = signs[n] == 0 ? 0 : (signs[n] > 0 ? 1 : -1);
        }

        segment_tree<sign, mult<sign>> segtree(signs.begin(), signs.end(), 1);

        while (K--)
        {
            char op;
            int i, j;
            cin >> op >> i >> j;

            switch (op)
            {
            case 'C':
            case 'c':
            {
                sign sign_j = j == 0 ? 0 : (j > 0 ? 1 : -1);
                segtree.update(i - 1, sign_j);
                break;
            }
            case 'P':
            case 'p':
            {
                sign result = segtree.query_range(i - 1, j);
                cout << (result == 0 ? '0' : (result > 0 ? '+' : '-'));
                break;
            }
            }
        }

        cout << '\n';
    }

    return 0;
}