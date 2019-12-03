#include <iostream>
#include <vector>

using namespace std;

int find_root(vector<int>& parent, int index)
{
    int parent_indx = parent[index];
    if(parent_indx == -1)
        return index;

    parent[index] = find_root(parent, parent_indx);
    return parent[index];
}

    
void merge(vector<int>& parent, int a, int b)
{
    int group_a = find_root(parent, a);
    int group_b = find_root(parent, b);

    if(group_a == group_b)
        return;

    parent[group_a] = group_b;
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<int> parent;
    parent.resize(N + 1, -1);

    for(int m = 0; m < M; ++m)
    {
        int op, a, b;
        cin >> op >> a >> b;

        switch(op)
        {
        case 0:
        {
            merge(parent, a, b);
            break;
        }
        case 1:
        {
            int group_a = find_root(parent, a);
            int group_b = find_root(parent, b);
            if(group_a == group_b)
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