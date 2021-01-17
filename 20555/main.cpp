#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <deque>

using namespace std;
using code_t = unsigned long long;
const size_t MAX_STR_CNT = sizeof(code_t);

union code_decode_t
{
    code_t code;
    unsigned char sz[MAX_STR_CNT];
};

struct task_t
{
    code_t code;
    string str;
};

code_t create_answer_code(const vector<string>& strs)
{
    code_decode_t decoder;
    for(size_t i = 0; i < MAX_STR_CNT; ++i)
    {
        decoder.sz[i] = strs[i].size();
    }

    return decoder.code;
}

code_t create_next_code(const vector<string>& strs, code_t current, char ch)
{
    code_decode_t decoder;
    decoder.code = current;

    for(size_t i = 0; i < MAX_STR_CNT; ++i)
    {
        if(strs[i].size() != decoder.sz[i] && strs[i][decoder.sz[i]] == ch)
        {
            decoder.sz[i]++;
        }
    }

    return decoder.code;
}

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    vector<string> strs(MAX_STR_CNT, "");
    for(size_t n = 0; n < N; ++n)
    {
        cin >> strs[n];
    }

    code_t answer_code = create_answer_code(strs);

    deque<task_t> tasks;
    tasks.push_back({ 0, "" });
    set<code_t> visited;
    while(true)
    {
        task_t current = tasks.front();
        tasks.pop_front();

        if(current.code == answer_code)
        {
            cout << current.str << '\n';
            break;
        }

        //cout << "current : " << current.code << " : " << (current.str) << endl;
        const auto check_ch = [&](char ch) {
            code_t next_code = create_next_code(strs, current.code, ch);
            if(next_code != current.code && visited.find(next_code) == visited.end())
            {
                //cout << "inserted : " << next_code << " : " << (current.str + ch) << endl;
                tasks.push_back({ next_code, current.str + ch });
                visited.insert(next_code);
            }
        };

        check_ch('A');
        check_ch('B');
        check_ch('C');
        check_ch('D');

        //cout << "---" << endl;
    }

    return 0;
}