#include <iostream>
#include <vector>
#include <array>
#include <numeric>


using namespace std;

constexpr size_t pow2(int n)
{
    return 1 << n;
}

// create segtree of length : 2^n
// memory required : 2^(n + 2)
//template type / default / op
template <typename _VAL_TYPE, _VAL_TYPE _DEFAULT_VAL, typename _OP>
struct BinarySegTree
{
    const size_t linear_size;
    const size_t total_size;

    vector<bool> _updated;
    vector<_VAL_TYPE> _seg;


    BinarySegTree(int n)
        : linear_size(pow2(n)), total_size(pow2(n + 1))
    {
        _updated.resize(total_size, false);
        _seg.resize(total_size, _DEFAULT_VAL);
    }

    constexpr size_t base(size_t height)
    {
        size_t sum = 0;
        while(height-- != 0)
            sum += (linear_size >> height);
        return sum;
    }

    constexpr size_t parent(size_t indx)
    {
        indx = indx / 2;
        return indx + linear_size;
    }

    constexpr size_t childLeft(size_t indx)
    {
        return indx * 2 - total_size;
    }

    constexpr size_t childRight(size_t indx)
    {
        return childLeft(indx) + 1;    
    }

    constexpr bool isLeft(size_t indx)
    {
        return indx % 2 == 0;
    }

    constexpr bool isRight(size_t indx)
    {
        return !isLeft(indx);
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
            _seg[it] = _DEFAULT_VAL;
            _updated[it] = true;
        }
        for(size_t it = linear_size; it < total_size; ++it)
        {
            _seg[it] = _DEFAULT_VAL;
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
    _VAL_TYPE calc(size_t begin, size_t end)
    {
        if(begin >= linear_size)
            return 0;
        if(end > linear_size)
            return 0;
        if(begin >= end)
            return 0;
        
        return _calc(begin, end -1);
    }

    // [s, e]
    _VAL_TYPE _calc(size_t s, size_t e)
    {
        if(s > e)
            return 0;
        if(s == e)
            return getVal(s);

        size_t parent_s = parent(s);
        size_t parent_e = parent(e);
        _VAL_TYPE result = _DEFAULT_VAL;
        if(isRight(s))
        {
            parent_s++;
            result = _OP()(result, getVal(s));
        }
        if(isLeft(e))
        {
            parent_e--;
            result = _OP()(result, getVal(e));
        }

        result += _calc(parent_s, parent_e);
        
        return result;
    }

    _VAL_TYPE getVal(size_t indx)
    {
        if(_updated[indx])
            return _seg[indx];
        
        _VAL_TYPE left = getVal(childLeft(indx));
        _VAL_TYPE right = getVal(childRight(indx));

        _seg[indx] = _OP()(left, right);
        _updated[indx] = true;

        return _seg[indx];
    }
};

using val_t = long long;

struct sum
{
    val_t operator() (const val_t& lhs, const val_t& rhs)
    {
        return lhs + rhs;
    }
};

vector<val_t> buff;
BinarySegTree<val_t, 0, sum> tree(20);

int main(int argc, char** argv)
{
    // WTF
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N, M, K;
    cin >> N >> M >> K;

    buff.resize(N, 0);
    for (int n = 0; n < N; ++n)
    {
        cin >> buff[n];
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
            tree.set(b - 1, c);
            break;
        case 2:
            int min = b < c ? b : c;
            int max = b < c ? c : b;
            val_t result = tree.calc(b - 1, (size_t)(c));
            cout << result << '\n';
            break;
        }
    }
}





