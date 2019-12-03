#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<size_t> elem_to_group;
    vector<set<size_t>> group_list;
    elem_to_group.resize(N + 1);
    group_list.resize(N + 1);
    for(int n = 0; n < N + 1; ++n)
    {
        elem_to_group[n] = n;
        group_list[n] = { n };
    }


    for(int m = 0; m < M; ++m)
    {
        int op, a, b;
        cin >> op >> a >> b;

        switch(op)
        {
        case 0:
        {
            const auto group_id_a = elem_to_group[a];
            const auto group_id_b = elem_to_group[b];

            if(group_id_a == group_id_b)
                break;

            auto& group_a = group_list[group_id_a];
            auto& group_b = group_list[group_id_b];

            if(group_a.size() > group_b.size())
            {
                // merge b to a
                for(const auto& elem_b : group_b)
                {
                    group_a.insert(elem_b);
                    elem_to_group[elem_b] = group_id_a;
                }

                group_b.clear();
            }
            else
            {
                // merge a to b
                for(const auto& elem_a : group_a)
                {
                    group_b.insert(elem_a);
                    elem_to_group[elem_a] = group_id_b;
                }

                group_a.clear();
            }
            
            break;
        }
        case 1:
        {
            const auto group_id_a = elem_to_group[a];
            const auto group_id_b = elem_to_group[b];

            if(group_id_a == group_id_b)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
            break;
        }
        }

    }

    return 0;
}