#include <iostream>
#include <vector>
#include <deque>


using namespace std;
enum state { NONE, LADDER, DISABLED };
using ladders_t = vector<vector<state>>;

void addLadder(ladders_t& ladder, int n, int h)
{
    const int N = ladder.size();
    ladder[n][h] = LADDER;
    if(n - 1 >= 0)
        ladder[n - 1][h] = DISABLED;
    if(n + 1 <= N - 1)
        ladder[n + 1][h] = DISABLED;
}

struct ladder_task
{
    int n, h;
};


int main(int argc, char** argv)
{
    int N, M, H;
    cin >> N >> M >> H;

    ladders_t init_lads;
    init_lads.resize(N - 1);
    for(auto& l : init_lads) l.resize(H, NONE);

    for(int m = 0; m < M; ++m)
    {
        int a, b;
        cin >> a >> b;
        addLadder(init_lads, b - 1, a - 1);
    }

    auto isComplete = [N, H](const ladders_t& ladders) -> bool
    {
        for(int i = 0; i < N - 1; ++i)
        {
            int current = i;
            for(int j = 0; j < H; ++j)
            {
                if(current < N - 1 && ladders[current][j] == LADDER)
                    current++;
                else if (current > 0 && ladders[current - 1][j] == LADDER)
                    current--;
            }

            if(current != i)
                return false;
        }

        return true;
    };

    bool found = false;
    deque<vector<ladder_task>> tasks;
    tasks.push_back({});

    while(!tasks.empty())
    {
        ladders_t cur_lads = init_lads;

        vector<ladder_task> cur_tasks = tasks.front();
        tasks.pop_front();

        if(cur_tasks.size() > 3)
            continue;

        for(auto& t : cur_tasks) 
            addLadder(cur_lads, t.n, t.h);

        if(isComplete(cur_lads))
        {
            int count = 0;
            for(auto& i : cur_lads)
                for(auto& j : i)
                    if(j == LADDER)
                        count++;
            
            found = true;
            cout << cur_tasks.size() << endl;
            break;
        }


        ladder_task last = { .n= 0, .h = 0};
        if(!cur_tasks.empty()) 
            last = cur_tasks.back();

        if(cur_tasks.size() == 3)
            continue;
        
        for(int j = last.h; j < H; ++j)
        {
            for(int i = 0; i < N - 1; ++ i)
            {
                if(j == last.h && i < last.n)
                    continue;

                if(cur_lads[i][j] == NONE)
                {
                    cur_tasks.push_back({ .n = i, .h = j});
                    tasks.push_back(cur_tasks);
                    cur_tasks.pop_back();
                }
            }
        }




    }

    if(!found)
        cout << "-1\n";

    return 0;
}