#include <iostream>
#include <vector>

using namespace std;

// create segtree of length : 2^n
// memory required : 2^(n + 2)
//template type / default / op
template <typename _VAL_TYPE, class _OP>
struct BinarySegTree
{
    BinarySegTree(int n)
        : linear_size(pow2(n)), total_size(pow2(n + 1))
    {
        _updated.resize(total_size, false);
        _seg.resize(total_size, _VAL_TYPE());
    }

    void init(const vector<_VAL_TYPE>& buff)
    {
        if(buff.size() > linear_size)
            return;

        for(size_t it = 0; it < buff.size(); ++it)
        {
            _seg[it] = buff[it];
            _updated[it] = true;
        }
        for(size_t it = buff.size(); it < linear_size; ++it)
        {
            _seg[it] = _VAL_TYPE();
            _updated[it] = true;
        }
        for(size_t it = linear_size; it < total_size; ++it)
        {
            _seg[it] = _VAL_TYPE();
            _updated[it] = false;
        }
    }

    void clearCache()
    {
        for(size_t it = linear_size; it < total_size; ++it)
        {
            _updated[it] = false;
        }
    }


    void set(size_t indx, _VAL_TYPE val)
    {
        if(indx >= linear_size)
            return;

        _seg[indx] = val;
        _updated[indx] = true;

        // set all parents not updated
        while(indx != total_size - 1)
        {
            indx = parent(indx);
            _updated[indx] = false;
        }
    }

    // [begin, end)
    _VAL_TYPE calc(size_t begin, size_t end, _OP op = _OP())
    {
        if(begin >= linear_size)
            return _VAL_TYPE();
        if(end > linear_size)
            return _VAL_TYPE();
        if(begin >= end)
            return _VAL_TYPE();
        
        return _calc(begin, end -1, op);
    }

private:
    const size_t linear_size;
    const size_t total_size;

    vector<bool> _updated;
    vector<_VAL_TYPE> _seg;


    // [s, e]
    _VAL_TYPE _calc(size_t s, size_t e, _OP op)
    {
        if(s > e)
            return _VAL_TYPE();
        if(s == e)
            return _getVal(s, op);

        size_t parent_s = parent(s);
        size_t parent_e = parent(e);
        _VAL_TYPE result = _VAL_TYPE();
        
        bool is_right_s = s % 2 == 1;
        if(is_right_s)
        {
            parent_s++;
            result = op(result, _getVal(s, op));
        }
        bool is_left_e = e % 2 == 0;
        if(is_left_e)
        {
            parent_e--;
            result = op(result, _getVal(e, op));
        }

        result = op(result, _calc(parent_s, parent_e, op));
        
        return result;
    }

    _VAL_TYPE _getVal(size_t indx, _OP op)
    {
        if(_updated[indx])
            return _seg[indx];
        
        _VAL_TYPE left = _getVal(childLeft(indx), op);
        _VAL_TYPE right = _getVal(childRight(indx), op);

        _seg[indx] = op(left, right);
        _updated[indx] = true;

        return _seg[indx];
    }

    constexpr size_t parent(size_t indx) const
    {
        indx = indx / 2;
        return indx + linear_size;
    }

    constexpr size_t childLeft(size_t indx) const
    {
        return indx * 2 - total_size;
    }

    constexpr size_t childRight(size_t indx) const
    {
        return childLeft(indx) + 1;    
    }
    
    constexpr size_t pow2(const int n) const
    {
        return 1 << n;
    }
};

using val_t = struct { long long val = 1; };
#define DIV 1000000007

struct mult
{
    val_t operator() (const val_t& lhs, const val_t& rhs)
    {
        return {(lhs.val * rhs.val) % DIV};
    }
};

vector<val_t> buff;
BinarySegTree<val_t, mult> tree(20);

int main(int argc, char** argv)
{
    // WTF
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N, M, K;
    cin >> N >> M >> K;

    buff.resize(N);
    for (int n = 0; n < N; ++n)
    {
        cin >> buff[n].val;
    }

    tree.init(buff);

    for (int mk = 0; mk < M + K; ++mk)
    {
        int a;
        size_t b;
        long long c;
        cin >> a >> b >> c;

        switch (a)
        {
        case 1:
            tree.set(b - 1, {c});
            break;
        case 2:
            size_t min = b < c ? b : c;
            size_t max = b < c ? c : b;
            val_t result = tree.calc(min - 1, max);
            cout << (result.val % DIV)<< '\n';
            break;
        }
    }
}

