#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct question
{
    int deadline;
    int cupnoodle;
};

int jump(vector<int>& table, int index)
{
    if (index == -1)
        return -1;

    if (table[index] != index)
    {
        int p = jump(table, table[index]);
        table[index] = p;
    }

    return table[index];

}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<question> questions;
    questions.resize(N);
    for (int n = 0; n < N; ++n)
    {
        cin >> questions[n].deadline >> questions[n].cupnoodle;
        questions[n].deadline--;
    }

    sort(questions.begin(), questions.end(), [](const question& lhs, const question& rhs)
    {
        return lhs.cupnoodle == rhs.cupnoodle ? lhs.deadline > rhs.deadline : lhs.cupnoodle > rhs.cupnoodle;
    });

    vector<int> jump_table;
    jump_table.resize(N);
    for (int n = 0; n < N; ++n)
    {
        jump_table[n] = n;
    }

    int sum = 0;
    for (int n = 0; n < N; ++n)
    {
        int index = jump(jump_table, questions[n].deadline);

        if (index != -1)
        {
            jump_table[index] = index - 1;
            sum += questions[n].cupnoodle;
        }
    }

    cout << sum << endl;

    return 0;
}
