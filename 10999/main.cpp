#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class lazy_segment_tree
{
public:
    using value_type = long long;
    using delta_type = long long;
    using size_type = size_t;
private:
    using depth_type = size_t;
    using lazy_val_type = struct {
        value_type val;
        delta_type delt;
    };

private:
    const value_type _default_val;
    const delta_type _default_delt;
    vector<vector<lazy_val_type>> _data;
    vector<size_type> _coverage;

public:
    lazy_segment_tree(vector<value_type> data, const value_type& default_val, const delta_type& default_delt)
        : lazy_segment_tree(data.begin(), data.end(), default_val, default_delt)
    {

    }


    template <class _ForwardIt>
    lazy_segment_tree(_ForwardIt begin, _ForwardIt end, const value_type& default_val, const delta_type& default_delt)
        : _default_val(default_val), _default_delt(default_delt)
    {
        depth_type depth = 0;
        _data.push_back({});
        for (auto it = begin; it != end; ++it)
        {
            _data[0].push_back({ *it, default_delt });
        }

        size_type N = _data[0].size();
        N = N == 1 ? 0 : (N + 1) >> 1;

        while (N > 0)
        {
            _data.push_back({});
            _data.back().resize(N, { default_val, default_delt });
            auto& prev = _data[_data.size() - 2];

            size_type n = 0;
            while (n < N - 1)
            {
                _data.back()[n].val = prev[n << 1].val + prev[(n << 1) + 1].val;
                ++n;
            }

            if ((n << 1) + 1 < prev.size())
                _data.back()[n].val = prev[n << 1].val + prev[(n << 1) + 1].val;
            else
                _data.back()[n].val = prev[n << 1].val;

            N = N == 1 ? 0 : (N + 1) >> 1;
        }

        _coverage.push_back(1);
        while (_coverage.size() < _data.size())
            _coverage.push_back(_coverage.back() << 1);
    }

private:


public:
    void update_range(size_type begin, size_type end, delta_type delta)
    {
        if (end <= begin)
            return;
        if (_data[0].size() < end)
            return;

        _update_range(begin, end, delta, 0, _data.size() - 1, 0, _data[0].size());
    }

    value_type query_range(size_type begin, size_type end)
    {
        if (end <= begin)
            return _default_val;
        if (_data[0].size() < end)
            return _default_val;

        return _query_range(begin, end, 0, _data.size() - 1, 0, _data[0].size());
    }

private:

    void _update_range(const size_type& up_begin, const size_type& up_end, const delta_type& delta,
                       const size_type i, const depth_type depth,
                       const size_type cov_begin, const size_type cov_end)
    {
        if (cov_begin >= up_end || cov_end <= up_begin || i >= _data[depth].size())
            return;

        if (up_begin <= cov_begin && cov_end <= up_end)
        {
            _data[depth][i].delt += delta;
            return;
        }

        if (depth == 0)
            return;

        const size_type range = min(up_end, cov_end) - max(up_begin, cov_begin);
        _data[depth][i].val += delta * range;

        const size_type left_child = i << 1;
        const size_type right_child = (i << 1) + 1;
        const size_type cov_mid = _coverage[depth - 1] + cov_begin;

        _update_range(up_begin, up_end, delta, left_child, depth - 1, cov_begin, cov_mid);
        _update_range(up_begin, up_end, delta, right_child, depth - 1, cov_mid, cov_end);
    }

    void _propagte(const size_type i, const depth_type depth, const size_type range, 
                   const size_type left_child, const size_type right_child)
    {
        if (_data[depth][i].delt == 0)
            return;

        _data[depth][i].val += _data[depth][i].delt * range;

        if (depth != 0)
        {
            if (left_child < _data[depth - 1].size())
                _data[depth - 1][left_child].delt += _data[depth][i].delt;
            if (right_child < _data[depth - 1].size())
                _data[depth - 1][right_child].delt += _data[depth][i].delt;
        }

        _data[depth][i].delt = 0;
    }

    value_type _query_range(const size_type& query_begin, const size_type& query_end, 
                            const size_type i, const depth_type depth, 
                            const size_type cov_begin, const size_type cov_end)
    {
        if (cov_begin >= query_end || cov_end <= query_begin || i >= _data[depth].size())
            return 0;

        const size_type left_child = i << 1;
        const size_type right_child = (i << 1) + 1;
        const size_type cov_mid = _coverage[depth - 1] + cov_begin;

        _propagte(i, depth, cov_end - cov_begin, left_child, right_child);

        if (depth == 0)
            return _data[0][i].val;
        if (query_begin <= cov_begin && cov_end <= query_end)
            return _data[depth][i].val;

        return _query_range(query_begin, query_end, left_child, depth - 1, cov_begin, cov_mid)
            + _query_range(query_begin, query_end, right_child, depth - 1, cov_mid, cov_end);
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K;
    cin >> N >> M >> K;

    vector<long long> buff;
    buff.resize(N);

    for (int n = 0; n < N; ++n)
    {
        cin >> buff[n];
    }

    lazy_segment_tree segtree(buff.begin(), buff.end(), 0, 0);

    for (int mk = 0; mk < M + K; ++mk)
    {
        int op;
        cin >> op;

        switch (op)
        {
        case 1:
        {
            size_t b, c;
            long long d;
            cin >> b >> c >> d;

            segtree.update_range(b - 1, c, d);

            break;
        }
        case 2:
        {
            size_t b, c;
            cin >> b >> c;

            auto result = segtree.query_range(b - 1, c);
            cout << result << '\n';

            break;
        }
        }
    }

    return 0;
}

