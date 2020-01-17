#include <iostream>
#include <vector>
#include <set>

using namespace std;

class segment_tree
{
private:
    const int _default_value = 0;
    vector<vector<int>> _data;
    size_t _size;

public:
    segment_tree(size_t N) : _size(N)
    {
        while (N > 0)
        {
            _data.push_back({});
            _data.back().resize(N, _default_value);

            if (N % 2 == 0)
                N = N >> 1;
            else if (N != 1)
                N = (N >> 1) + 1;
            else
                N = 0;
        }
    }

    constexpr size_t size() const
    {
        return _size;
    }

    void update(size_t index, int value)
    {
        _data[0][index] = value;

        index = index >> 1;
        size_t depth = 1;
        while (depth < _data.size())
        {
            const auto _child_left = index << 1;
            const auto _child_right = _child_left + 1;

            _data[depth][index] = _data[depth - 1][_child_left];
            if (_child_right < _data[depth - 1].size())
                _data[depth][index] += _data[depth - 1][_child_right];

            index = index >> 1;
            depth += 1;
        }
    }

    int get_val(size_t index)
    {
        return _data[0][index];
    }

    size_t query(int nth)
    {
        size_t index = 0;
        size_t depth = _data.size() - 1;
        while (depth != 0)
        {
            const size_t _child_left = index << 1;
            const size_t _child_right = _child_left + 1;

            if (nth <= _data[depth - 1][_child_left])
            {
                index = _child_left;
            }
            else
            {
                index = _child_right;
                nth -= _data[depth - 1][_child_left];
            }

            depth--;
        }

        return index;
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    segment_tree candy_box(1000000);

    int N;
    cin >> N;

    while (N--)
    {
        int op;
        cin >> op;

        switch (op)
        {
        case 1:
        {
            int nth;
            cin >> nth;

            size_t taste = candy_box.query(nth);
            cout << (taste + 1) << '\n';

            int current = candy_box.get_val(taste);
            candy_box.update(taste, current - 1);
            break;
        }
        case 2:
        {
            int a, b;
            cin >> a >> b;

            int current = candy_box.get_val(a - 1);
            candy_box.update(a - 1, current + b);
            break;
        }
        }
    }

    return 0;
}
