#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>

using namespace std;
struct pos_t 
{ 
    int x = 0; int y = 0; 
    constexpr bool operator == (const pos_t& other) const { return other.x == x && other.y == y; }
};
namespace std
{
    template<>
    struct hash<pos_t>
    {
        size_t operator()(const pos_t& val) const { return hash<int>()(~val.x) ^ hash<int>()(val.y); }
    };
};
using snake_t = deque<pos_t>;
using apples_t = unordered_set<pos_t>;
enum dir_t { up, right, down, left };
constexpr dir_t rotate_r(const dir_t& dir) { return dir == 3 ? dir_t::up : (dir_t)(dir + 1); }
constexpr dir_t rotate_l(const dir_t& dir) { return dir == 0 ? dir_t::left : (dir_t)(dir - 1); }

bool simulate(const int N, snake_t& snake, apples_t& apples, dir_t dir)
{
    // step 1
    pos_t next = snake.front();
    switch(dir)
    {
    case dir_t::up:
    {
        next.y--;
        if(next.y < 0)
            return false;
        break;
    }
    case dir_t::right:
    {
        next.x++;
        if(next.x >= N)
            return false;
        break;
    }
    case dir_t::down:
    {
        next.y++;
        if(next.y >= N)
            return false;
        break;
    }
    case dir_t::left:
    {
        next.x--;
        if(next.x < 0)
            return false;
        break;
    }

    }

    // step 2
    auto body = snake.begin();
    while(body != snake.end())
    {
        if(*body == next)
            return false;
        body++;
    }

    // step 3
    auto apple_exists = apples.find(next);
    if(apple_exists != apples.end())
    {
        // eat apple
        apples.erase(apple_exists);
        snake.push_front(next);
    }
    else
    {
        snake.push_front(next);
        snake.pop_back();
    }

    return true;
}


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    int A;
    cin >> A;
    
    apples_t apples;
    for(int i = 0; i < A; ++i)
    {
        int x, y;
        cin >> y >> x;
        apples.insert({ x - 1, y - 1});
    }

    int opcount;
    cin >> opcount;

    int rotate_time = 0;
    char rotate_dir = 'R';
    if(opcount > 0)
    {
        cin >> rotate_time >> rotate_dir;
        opcount--;
    }



    snake_t snake;
    snake.push_front({ 0, 0 });
    dir_t dir = dir_t::right;

    int time = 0;
    while(simulate(N, snake, apples, dir))
    {
        time++;
        if(time == rotate_time)
        {
            if(rotate_dir == 'L')
                dir = rotate_l(dir);
            else
                dir = rotate_r(dir);

            if(opcount > 0)
            {
                cin >> rotate_time >> rotate_dir;
                opcount--;
            }
        }
    }

    while(opcount > 0)
    {
        cin >> rotate_time >> rotate_dir;
        opcount--;
    }

    cout << time + 1 << endl;

    return 0;
}



