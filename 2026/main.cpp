#include <iostream>
#include <vector>
#include <set>

using namespace std;

using friends_t = vector<set<int>>;

bool solve(const friends_t &friends, const int &K, vector<int> &candidates)
{
    if(candidates.size() == K)
        return true;

    int last = candidates.back();

    for (auto &f : friends[last])
    {
        bool is_f_candidate = true;
        for (const auto &c : candidates)
        {
            if (friends[c].find(f) == friends[c].end())
            {
                is_f_candidate = false;
                break;
            }
        }

        if (is_f_candidate)
        {
            candidates.push_back(f);
            bool is_sovled = solve(friends, K, candidates);
            if(is_sovled)
                return true;
            candidates.pop_back();
        }
    }

    return false;
}


int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int K, N, F;
    cin >> K >> N >> F;

    friends_t friends;
    friends.resize(N);

    while (F--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        if (a < b)
        {
            friends[a].insert(b);
        }
        else
        {
            friends[b].insert(a);
        }
    }

    vector<int> candidates;
    bool is_solved = false;
    for (int i = 0; i < N; ++i)
    {
        candidates.push_back(i);

        is_solved = solve(friends, K, candidates);
        if(is_solved)
        {
            for(auto& i : candidates)
            {
                cout << (i + 1) << '\n';
            }
            break;
        }

        candidates.pop_back();
    }

    if(!is_solved)
    {
        cout << "-1\n";
    }

    return 0;
}