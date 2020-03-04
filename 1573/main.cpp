#include <iostream>
#include <vector>
#include <string>

using namespace std;


// cannot compile string_view
void solve(const vector<int>& F, int Index, const std::string& char_set, int c_begin, int c_end, vector<char>& answer)
{
    int N = c_end - c_begin;
    if(N == 0)
        return;

    //cout << "(" << N << ", " << Index << ") : " << char_set << endl;

    for(size_t i = 0; i < N; ++i)
    {
        int current = F[i] * F[(N - 1) - i];
        if(Index < current)
        {
            answer.push_back(char_set[c_begin + i]);

            solve(F, Index / F[(N - 1) - i], char_set, c_begin, c_begin + i, answer);
            solve(F, Index % F[(N - 1) - i], char_set, c_begin + i + 1, c_end, answer);

            break;
        }
        else
        {
            Index -= current;
        }
    }
}


int main(int argc, char** argv)
{
    vector<int> F;
    F.resize(20, 0);

    F[0] = 1;
    F[1] = 1;
    for(size_t i = 2; i < F.size(); ++i)
    {
        for(size_t j = 0; j < i; ++j)
        {
            F[i] += F[j] * F[(i - 1) - j];
        }
    }

    int N;
    int Index;
    cin >> N >> Index;
    Index--;

    string char_set = "abcdefghijklmnopqrstuvwxyz";
    vector<char> answer;

    if(Index < F[N])
    {
        solve(F, Index, char_set, 0, N, answer);
        for(const char& ans : answer)
            cout << ans;
        cout << '\n';
    }
    else
    {
        cout << "-1\n";
    }

    cout << endl;

    return 0;
}