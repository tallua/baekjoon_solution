#include <iostream>
#include <vector>

using namespace std;
using sz_t = unsigned int;
using id_t = unsigned int;

void retreive_graph(const vector<vector<id_t>> &precede, const vector<vector<id_t>>& successor,
    id_t current, vector<sz_t> &group, sz_t current_group, vector<id_t> &result)
{
    for(const id_t& s : successor[current])
        if(group[s] == 0)
            return;

    //cout << "stacking : " << current << endl;
            
    group[current] = current_group;
    result.push_back(current);

    for (const id_t &p : precede[current])
    {
        if (group[p] == 0)
            retreive_graph(precede, successor, p, group, current_group, result);
    }

}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    sz_t N, M;
    cin >> N >> M;

    vector<vector<id_t>> precede;
    vector<vector<id_t>> successor;
    precede.resize(N);
    successor.resize(N);

    for (sz_t m = 0; m < M; ++m)
    {
        sz_t cnt;
        cin >> cnt;

        if (cnt == 0)
            continue;

        sz_t before;
        cin >> before;
        before--;

        for (sz_t c = 1; c < cnt; ++c)
        {
            sz_t current;
            cin >> current;
            current--;

            precede[current].push_back(before);
            successor[before].push_back(current);

            before = current;
        }
    }

    vector<sz_t> groups;
    groups.resize(N);

    vector<id_t> result;
    result.reserve(N);

    sz_t group_id = 1;
    for (sz_t i = 0; i < groups.size(); ++i)
    {
        if (groups[i] == 0)
        {
            retreive_graph(precede, successor, i, groups, group_id++, result);
        }
    }

    if (result.size() == N)
    {
        for (auto r_it = result.rbegin(); r_it != result.rend(); ++ r_it)
            cout << ((*r_it) + 1) << '\n';
    }
    else
    {
        cout << "0\n";
    }

    cout << endl;

    return 0;
}