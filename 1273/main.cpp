#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class lazy_segtree
{
    struct _internal_data
    {
        int lazy;
        int current;
    };

    vector<_internal_data> _data;
    size_t _N;
    const int _default_val;

public:
    lazy_segtree(size_t N, int default_val = int())
        : _N(N), _default_val(default_val)
    {
        _data.resize(4 * N, { default_val, default_val });
    }

    void update_range(size_t begin, size_t end, int delta)
    {
        if (begin != end)
            _update_range(0, 0, _N - 1, begin, end - 1, delta);
    }

    int query_range(size_t begin, size_t end)
    {
        int result = _default_val;
        _query_range(0, 0, _N - 1, begin, end - 1, result);
        return result;
    }

    size_t index_query(int val)
    {
        return _index_query(0, 0, _N - 1, val);
    }

private:
    void _update_lazy(size_t x, size_t left, size_t right)
    {
        if (_data[x].lazy == _default_val)
            return;

        _data[x].current += _data[x].lazy * (right - left + 1);

        if (left != right)
        {
            _data[2 * x + 1].lazy += _data[x].lazy;
            _data[2 * x + 2].lazy += _data[x].lazy;
        }

        _data[x].lazy = _default_val;
    }

    void _update_range(size_t x, size_t left, size_t right, size_t front, size_t back, const int delta)
    {
        //_update_lazy(x, left, right);
        if (back < left || right < front)
            return;

        if (front <= left && right <= back)
        {
            _data[x].lazy += delta;
            return;
        }

        if (left == right)
            return;

        size_t l = max(left, front);
        size_t r = min(right, back);
        _data[x].current += (delta * (r - l + 1));

        size_t mid = (left + right) / 2;
        _update_range(2 * x + 1, left, mid, front, back, delta);
        _update_range(2 * x + 2, mid + 1, right, front, back, delta);
    }

    void _query_range(size_t x, size_t left, size_t right, size_t front, size_t back, int& result)
    {
        if (back < left || right < front)
            return;

        _update_lazy(x, left, right);
        if (front <= left && right <= back)
        {
            result += _data[x].current;
            return;
        }

        if (left == right)
            return;

        size_t mid = (left + right) / 2;
        _query_range(2 * x + 1, left, mid, front, back, result);
        _query_range(2 * x + 2, mid + 1, right, front, back, result);
    }


    size_t _index_query(size_t x, size_t left, size_t right, int val)
    {
        _update_lazy(x, left, right);
        if (left == right)
            return left;

        size_t mid = (left + right) / 2;
        _update_lazy(2 * x + 1, left, mid);
        if (_data[2 * x + 1].current < val)
        {
            return _index_query(2 * x + 2, mid + 1, right, val - _data[2 * x + 1].current);
        }
        else
        {
            return _index_query(2 * x + 1, left, mid, val);
        }
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    lazy_segtree can_info(3000000);
    lazy_segtree index_counter(1300000);
    index_counter.update_range(0, 1300000, 1);

    int N;
    cin >> N;

    vector<size_t> current_heights;
    current_heights.resize(N, 0);

    for (int n = 0; n < N; ++n)
    {
        size_t black;
        cin >> black;
        can_info.update_range(current_heights[n], current_heights[n] + black, 1);
        current_heights[n] += black;
    }

    for (int n = 0; n < N; ++n)
    {
        size_t grey;
        cin >> grey;
        can_info.update_range(current_heights[n], current_heights[n] + grey, 2);
        current_heights[n] += grey;
    }

    for (int n = 0; n < N; ++n)
    {
        size_t white;
        cin >> white;
        can_info.update_range(current_heights[n], current_heights[n] + white, 5);
    }

    int M;
    cin >> M;

    while (M--)
    {
        int m;
        cin >> m;

        size_t index = index_counter.index_query(m);
        index_counter.update_range(index, index + 1, -1);
        int result = can_info.query_range(index, index + 1);
        //cout << index << " : " << result << endl;
        cout << result << '\n';
    }

    return 0;
}