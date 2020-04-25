#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <limits>
#include <algorithm>

using namespace std;
using score_t = long long;
using trace_t = unsigned long long;

using group_t = vector<map<score_t, trace_t>>;

struct Sums
{
    score_t score;
    trace_t trace;
};

void build_groups(group_t& group, const vector<score_t>& scores_sum, const size_t start, const size_t size)
{
    const size_t N = scores_sum.size();

    group.resize(size + 1);
    group[0].insert({0, 0});

    for(size_t score_index = start; score_index < start + size; ++score_index)
    {
        for(size_t i = group.size() - 1; i > 0; --i)
        {
            for(auto g_it = group[i - 1].begin(); g_it != group[i - 1].end(); ++g_it)
            {
                score_t new_score = g_it->first + scores_sum[score_index];
                trace_t new_trace = g_it->second | (1ull << (N - score_index));
                if(group[i].find(new_score) != group[i].end())
                {
                    if(new_trace < group[i][new_score])
                        group[i][new_score] = new_trace;
                }
                else
                    group[i][new_score] = new_trace;
            }
        }
    }
}

void debug_groups(const group_t& group)
{
    for(size_t i = 0; i < group.size(); ++i)
    {
        cout << "starting " << i << endl;
        for(auto& g : group[i])
        {
            cout << g.first << " : " << g.second << endl;
        }
        cout << endl;
    }
}

Sums match(const vector<score_t>& scores_sum, const score_t target)
{
    const size_t N = scores_sum.size();
    const size_t half_N = N / 2;
    const size_t group_a_size = N / 2;
    const size_t group_b_size = N - group_a_size;

    group_t group_a, group_b;
    build_groups(group_a, scores_sum, 0, group_a_size);
    build_groups(group_b, scores_sum, group_a_size, group_b_size);
    //debug_groups(group_a);
    //debug_groups(group_b);

    Sums answer = { 72000000000000000ll, 0 };
    for(size_t i = 0; i < group_a.size(); ++i)
    {
        // compare group_a[i], group_b[half_N - i]
        auto a_it = group_a[i].begin();
        auto b_it = group_b[half_N - i].rbegin();

        while(a_it != group_a[i].end())
        {
            while(b_it != group_b[half_N - i].rend())
            {
                score_t new_score = a_it->first + b_it->first;
                trace_t new_trace = a_it->second | b_it->second;

                score_t new_diff = abs(target - new_score);
                score_t answer_diff = abs(target - answer.score);

                if(new_diff < answer_diff)
                {
                    answer.score = new_score;
                    answer.trace = new_trace;
                }
                else if(new_diff == answer_diff && new_trace < answer.trace)
                {
                    answer.trace = new_trace;
                }

                if(new_score <= target)
                    break;

                b_it++;
            }

            a_it++;
        }
    }

    return answer;
}


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    vector<score_t> scores_1;
    scores_1.resize(N);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> scores_1[n];
    }

    vector<score_t> scores_2;
    scores_2.resize(N);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> scores_2[n];
    }

    vector<score_t> scores_sum;
    scores_sum.resize(N);
    for(size_t i = 0; i < N; ++i)
    {
        scores_sum[i] = scores_2[i] + scores_1[i];
    }

    Sums answer = { 0, 0 };
    score_t sum_score_1 = accumulate(scores_1.begin(), scores_1.end(), (score_t)0);
    answer = match(scores_sum, sum_score_1);

    for(size_t n = 0; n < N; ++n)
    {
        bool is_team_2 = answer.trace & (1ull << (N - n));
        if(is_team_2)
            cout << "2 ";
        else
            cout << "1 ";
    }
    cout << endl;

    return 0;
}


