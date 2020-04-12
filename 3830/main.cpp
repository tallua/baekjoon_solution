#include <iostream>
#include <vector>

using namespace std;

class WorkReports
{
private:
    vector<int> _set;
    vector<int> _diff;

public:
    WorkReports()
    {
    }

    void clear_n_resize(size_t N)
    {
        _set.resize(N);
        _diff.clear();
        _diff.resize(N, 0);
        for (size_t n = 0; n < N; ++n)
        {
            _set[n] = n;
        }
    }

    void merge(size_t a, size_t b, int diff)
    {
        size_t set_a = _get_set(a);
        size_t set_b = _get_set(b);
        
        if(set_a == set_b)
            return;

        _set[set_b] = set_a;
        _diff[set_b] = _diff[a] + diff - _diff[b];
    }

    bool query(size_t a, size_t b, int& diff)
    {
        size_t set_a = _get_set(a);
        size_t set_b = _get_set(b);

        if(set_a != set_b)
            return false;

        diff = _diff[b] - _diff[a];
        return true;
    }

private:
    size_t _get_set(size_t index)
    {
        const size_t parent = _set[index];
        if(parent == index)
            return index;

        _set[index] = _get_set(parent);
        _diff[index] += _diff[parent];

        return _set[index];
    }
};

int main(int argc, char **argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    WorkReports reports;
    int N, M;
    do
    {
        cin >> N >> M;
        if(N == 0 && M == 0)
            break;

        reports.clear_n_resize(N);

        while (M--)
        {
            char op;
            size_t a, b;
            int diff;

            cin >> op >> a >> b;
            if(op == '!')
            {
                cin >> diff;

                reports.merge(a - 1, b - 1, diff);
            }
            else
            {
                if(reports.query(a - 1, b - 1, diff))
                {
                    cout << diff << '\n';
                }
                else
                {
                    cout << "UNKNOWN\n";
                }
            }
        }
    } while(true);

    cout << endl;

    return 0;
}
