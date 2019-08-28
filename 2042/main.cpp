#include <iostream>
#include <vector>
#include <array>
#include <numeric>

using namespace std;

using val_t = long long;
#define ARR_SIZE 1000000

template <size_t N>
struct pow2
{
    enum { val = 2 * pow2<N - 1>::val };
};

template <>
struct pow2<0>
{
    enum { val = 1 };
};


template <size_t N>
struct SegTree
{
    array<bool, pow2<N + 1>::val> _updated;
    array<val_t, pow2<N + 1>::val> _seg;

    constexpr size_t base(size_t height)
    {
        size_t sum = 0;
        while(height-- != 0)
            sum += (pow2<N>::val >> height);
        return sum;
    }

    constexpr size_t parent(size_t indx)
    {
        indx = indx / 2;
        return indx + pow2<N>::val;
    }

    constexpr size_t childLeft(size_t indx)
    {
        return indx * 2 - pow2<N + 1>::val;
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

    void init(const array<val_t, pow2<N>::val>& buff)
    {
        if(buff.size() > pow2<N>::val)
            return;

        _updated.fill(false);
        for(size_t it = 0; it < buff.size(); ++it)
        {
            _seg[it] = buff[it];
            _updated[it] = true;
        }
    }

    void set(size_t indx, val_t val)
    {
        if(indx >= pow2<N>::val)
            return;

        _seg[indx] = val;
        _updated[indx] = true;

        // set all parents not updated
        while(indx != pow2<N + 1>::val - 1)
        {
            indx = parent(indx);
            _updated[indx] = false;
        }
    }

    // [begin, end)
    val_t sum(size_t begin, size_t end)
    {
        if(begin >= pow2<N>::val)
            return 0;
        if(end > pow2<N>::val)
            return 0;
        if(begin >= end)
            return 0;
        
        
        return _sum(begin, end -1);
    }

    // [s, e]
    val_t _sum(size_t s, size_t e)
    {
        if(s > e)
            return 0;
        if(s == e)
            return getVal(s);

        size_t parent_s = parent(s);
        size_t parent_e = parent(e);
        val_t result = 0;
        if(isRight(s))
        {
            parent_s++;
            result += getVal(s);
        }
        if(isLeft(e))
        {
            parent_e--;
            result += getVal(e);
        }

        result += _sum(parent_s, parent_e);
        
        return result;
    }

    val_t getVal(size_t indx)
    {
        if(_updated[indx])
            return _seg[indx];
        
        val_t left = getVal(childLeft(indx));
        val_t right = getVal(childRight(indx));

        _seg[indx] = left + right;
        _updated[indx] = true;

        return _seg[indx];
    }
};

#define SIZE 20

array<val_t, pow2<SIZE>::val> buff;
SegTree<SIZE> tree;

int main(int argc, char** argv)
{
    // WTF
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N, M, K;
    cin >> N >> M >> K;

    buff.fill(0);
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
            val_t result = tree.sum(b - 1, (size_t)(c));
            cout << result << '\n';
            break;
        }
    }
}