#include <iostream>
#include <vector>

using namespace std;

struct segtree
{
    struct _Node
    {
        bool dirty;
        bool invert;
        int count;
    };

    vector<vector<_Node>> _data;
    vector<int> _area_size;

    segtree(int N)
    {
        int tmp = 1;
        while (tmp < N)
            tmp = tmp << 1;
        N = tmp;
        int area_size = 1;
        while (N >= 1)
        {
            _data.push_back({});
            _data.back().resize(N, { false, false, 0 });
            _area_size.push_back(area_size);

            area_size = area_size << 1;
            N = N >> 1;
        }
    }

    void invert(int s, int t)
    {
        _invert(s, t, 0);
    }

    int count(int s, int t)
    {
        return _count(s, t, 0);
    }

private:
    void _invert(int s, int t, int depth)
    {
        if (s == t)
        {
            // set dirty
            _data[depth][s].invert = !_data[depth][s].invert;
            _set_dirty(s, depth);
            return;
        }

        if (s % 2 == 1)
        {
            _invert(s, s, depth);
            s++;
        }

        if (t % 2 == 0)
        {
            _invert(t, t, depth);
            t--;
        }

        if (s <= t)
            _invert(s >> 1, t >> 1, depth + 1);
    }

    void _set_dirty(int s, int depth)
    {
        for (int d = depth; d < _data.size(); ++d)
        {
            _data[d][s].dirty = true;
            s = s >> 1;
        }
    }


    int _count(int s, int t, int depth)
    {
        if (s == t)
        {
            _clean(s, depth);
            if (_is_inverted(s >> 1, depth + 1))
            {
                return _area_size[depth] - _data[depth][s].count;
            }
            else
            {
                return _data[depth][s].count;
            }
        }

        int sum = 0;
        if (s % 2 == 1)
        {
            sum += _count(s, s, depth);
            s++;
        }
        if (t % 2 == 0)
        {
            sum += _count(t, t, depth);
            t--;
        }

        if (s <= t)
            sum += _count(s >> 1, t >> 1, depth + 1);

        return sum;
    }

    void _clean(int s, int depth)
    {
        if (_data[depth][s].dirty == false)
        {
            return;
        }

        if (depth == 0)
        {
            if (_data[depth][s].invert)
                _data[depth][s].count = 1;
            else
                _data[depth][s].count = 0;
        }
        else
        {
            int s2 = s << 1;
            _clean(s2, depth - 1);
            _clean(s2 + 1, depth - 1);

            if (_data[depth][s].invert)
            {
                _data[depth][s].count = _area_size[depth] - (_data[depth - 1][s2].count + _data[depth - 1][s2 + 1].count);
            }
            else
            {
                _data[depth][s].count = _data[depth - 1][s2].count + _data[depth - 1][s2 + 1].count;
            }
        }

        _data[depth][s].dirty = false;
    }

    bool _is_inverted(int s, int depth)
    {
        bool result = false;
        for (int d = depth; d < _data.size(); ++d)
        {
            result ^= _data[d][s].invert;
            s = s >> 1;
        }

        return result;
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    segtree lights(N);

    for (int m = 0; m < M; ++m)
    {
        int op, s, t;
        cin >> op >> s >> t;
        if (s > t)
            std::swap(s, t);

        switch (op)
        {
        case 0:
        {
            lights.invert(s - 1, t - 1);
            break;
        }
        case 1:
        {
            cout << lights.count(s - 1, t - 1) << '\n';
            break;
        }
        }
    }

    return 0;
}
