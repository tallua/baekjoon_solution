#include <iostream>
#include <set>
#include <deque>

using namespace std;

struct my_set
{
    multiset<uint16_t> left;
    multiset<uint16_t> right;

    void insert(uint16_t val)
    {
        if (left.empty())
            left.insert(val);
        else
        {
            if (val <= *left.rbegin())
                left.insert(val);
            else
                right.insert(val);

            _balance_one();
        }
    }

    void erase(uint16_t val)
    {

        if (val <= *left.rbegin())
        {
            auto it = left.find(val);
            left.erase(it);
        }
        else
        {
            auto it = right.find(val);
            right.erase(it);
        }

        _balance_one();
    }

    void _balance_one()
    {
        if (left.size() < right.size())
        {
            auto rotate = right.begin();
            left.insert(*rotate);
            right.erase(rotate);
        }
        else if (left.size() > right.size() + 1)
        {
            auto rotate = --left.end();
            right.insert(*rotate);
            left.erase(rotate);
        }
    }

    uint16_t mid() const
    {
        return *left.crbegin();
    }

    size_t size() const
    {
        return left.size() + right.size();
    }
};


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    my_set temperatures;
    deque<uint16_t> input_q;
    long long sum = 0;
    for (int n = 0; n < N; ++n)
    {
        uint16_t current;
        cin >> current;

        input_q.push_back(current);
        temperatures.insert(current);

        if (temperatures.size() > K)
        {
            temperatures.erase(input_q.front());
            input_q.pop_front();
        }

        if (temperatures.size() == K)
        {
            sum += temperatures.mid();
        }
    }

    cout << sum << endl;

    return 0;
}