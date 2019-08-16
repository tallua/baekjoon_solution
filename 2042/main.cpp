#include <iostream>
#include <vector>
#include <array>
#include <numeric>

using namespace std;

using val_t = long long;
using result_t = long long;

#define LEAF_CNT 1048576
#define NODE_SIZE 2
#define TREE_HEIGHT 19

template <size_t X, size_t E>
struct Pow
{
    enum { val = Pow<X, E - 1>::val * X };
};

template <size_t X>
struct Pow<X, 0>
{
    enum { val = 1 };
};

template <size_t Height>
struct NodeCount
{
    enum { val = LEAF_CNT / Pow<NODE_SIZE, Height>::val };
};

template<size_t Height>
struct Nodes
{
    std::array<val_t, NodeCount<Height>::val> data;
};

template<size_t Height>
struct Tree
{
    Nodes<Height> nodes;
    Tree<Height - 1> low;

    void init(const vector<val_t>& arr)
    {
        low.init(arr);

        size_t N = arr.size();
        for (size_t i = 0; i < ((N - 1) / Pow<NODE_SIZE, Height>::val) + 1; ++i)
        {
            val_t sum = 0;
            for (size_t j = i * NODE_SIZE; j < (i + 1) * NODE_SIZE; ++j)
                sum += low.getatheight(j);
            nodes.data[i] = sum;
        }
    }

    void set(const size_t& indx, const val_t& val)
    {
        low.set(indx, val);

        size_t i = (indx / Pow<NODE_SIZE, Height>::val);
        nodes.data[i] = low.sum(i * NODE_SIZE, (i + 1) * NODE_SIZE);
    }

    val_t get(const size_t& indx) const
    {
        return low.get(indx);
    }

    result_t getatheight(const size_t& indx) const
    {
        return nodes.data[indx];
    }

    result_t sum(const size_t& indx1, const size_t& indx2) const
    {

        size_t left_margin = (indx1 / Pow<NODE_SIZE, Height>::val) + 1;
        size_t right_margin = (indx2 / Pow<NODE_SIZE, Height>::val);

        if (indx1 >= indx2)
        {
            return 0;
        }
        else if (left_margin < right_margin)
        {
            result_t result = 0;
            for (size_t i = left_margin * NODE_SIZE; i < right_margin * NODE_SIZE; ++i)
            {
                result += nodes.data[i];
            }
            result += low.sum(indx1, left_margin * NODE_SIZE);
            result += low.sum(right_margin * NODE_SIZE, indx2);

            return result;
        }
        else
        {
            return low.sum(indx1, indx2);
        }
    }
};

template<>
struct Tree<0>
{
    Nodes<0> nodes;

    void init(const vector<val_t>& arr)
    {
        size_t len = arr.size();
        for (int i = 0; i < len; ++i)
        {
            nodes.data[i] = arr[i];
        }
    }

    void set(const size_t& indx, const val_t& val)
    {
        nodes.data[indx] = val;
    }

    val_t get(const size_t& indx) const
    {
        return nodes.data[indx];
    }

    result_t getatheight(const size_t& indx) const
    {
        return nodes.data[indx];
    }

    result_t sum(const size_t& indx1, const size_t& indx2) const
    {
        result_t result = accumulate(nodes.data.data() + indx1, nodes.data.data() + indx2, 0);

        return result;
    }
};

Tree<TREE_HEIGHT> tree;


int main(int argc, char** argv)
{
    // WTF
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N, M, K;
    cin >> N >> M >> K;

    vector<val_t> buff;
    buff.resize(N, 0);
    for (int n = 0; n < N; ++n)
    {
        int tmp;
        cin >> tmp;
        buff[n] = tmp;
    }

    tree.init(buff);

    for (int mk = 0; mk < M + K; ++mk)
    {
        int a, b, c;
        cin >> a >> b >> c;

        switch (a)
        {
        case 1:
            tree.set(b - 1, c);
            break;
        case 2:
            int min = b < c ? b : c;
            int max = b < c ? c : b;
            result_t result = tree.sum(b - 1, c);
            cout << result << '\n';
            break;
        }
    }
}