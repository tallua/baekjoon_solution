#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const size_t none_id = numeric_limits<size_t>::max();

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--)
    {
        size_t N, M;
        cin >> N >> M;

        using book_range = pair<size_t, size_t>;
        vector<book_range> graph;
        graph.resize(M);
        for (size_t m = 0; m < M; ++m)
        {
            size_t a, b;
            cin >> a >> b;
            a--;

            graph[m] = { a, b };
        }

        sort(graph.begin(), graph.end(), [](const book_range& lhs, const book_range& rhs) {
            return lhs.second != rhs.second ? lhs.second < rhs.second : lhs.first < rhs.first;
        });

        vector<bool> assigned;
        assigned.resize(N, false);

        size_t count = 0;
        for (const auto& range : graph)
        {
            for (size_t book_indx = range.first; book_indx < range.second; ++book_indx)
            {
                if (assigned[book_indx] == false)
                {
                    assigned[book_indx] = true;
                    count++;
                    break;
                }
            }
        }

        cout << count << '\n';
    }

    cout << endl;

    return 0;
}