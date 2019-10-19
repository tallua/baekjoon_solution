#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> map;
    map.resize(N);
    for(auto& l : map) l.resize(M, 0);
    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < M; ++x)
        {
            std::cin >> map[y][x];
        }
    }

    auto get_val = [N, M, &map](int y, int x) -> int
    {
        if(x < 0 || x >= M)
            return 0;
        if(y < 0 || y >= N)
            return 0;
        return map[y][x];
    };

    auto calc_max = [&](vector<vector<int>> frame) -> int
    {
        int local_max = 0;
        for(int y = 0; y < N; ++y)
        {
            for(int x = 0; x < M; ++x)
            {
                int sum = 0;
                for(int fy = 0; fy < frame.size(); ++fy)
                {
                    for(int fx = 0; fx < frame[fy].size(); ++fx)
                    {
                        if(frame[fy][fx] != 0)
                        {
                            sum += get_val(y + fy, x + fx);
                        }
                    }
                }

                if(sum > local_max)
                    local_max = sum;
            }
        }

        return local_max;
    };


    int global_max = 0;
    // [][][][]
    global_max = std::max(global_max, calc_max({{ 1, 1, 1, 1 }}));
    global_max = std::max(global_max, calc_max({ { 1 }, { 1 }, { 1 }, { 1 } }));

    // [][]
    // [][]
    global_max = std::max(global_max, calc_max({ { 1, 1 }, { 1, 1 }}));

    // []
    // [][][]
    global_max = std::max(global_max, calc_max({ { 1 }, { 1, 1, 1 } }));
    global_max = std::max(global_max, calc_max({ { 1, 1 }, { 1 }, { 1 } }));
    global_max = std::max(global_max, calc_max({ { 1, 1, 1 }, { 0, 0, 1 }}));
    global_max = std::max(global_max, calc_max({ { 0, 1 }, { 0, 1 }, { 1, 1 } }));

    //     []
    // [][][]
    global_max = std::max(global_max, calc_max({ { 0, 0, 1 }, { 1, 1, 1 } }));
    global_max = std::max(global_max, calc_max({ { 1, 1 }, { 0, 1 }, { 0, 1 } }));
    global_max = std::max(global_max, calc_max({ { 1 }, { 1 }, { 1, 1 } }));
    global_max = std::max(global_max, calc_max({ { 1, 1, 1 }, { 1 }}));

    // [][]
    //   [][]
    global_max = std::max(global_max, calc_max({ { 1, 1 }, { 0, 1, 1 }}));
    global_max = std::max(global_max, calc_max({ { 0, 1 }, { 1, 1 }, { 1 }}));
    
    //   [][]
    // [][]
    global_max = std::max(global_max, calc_max({ { 0, 1, 1 }, { 1, 1 }}));
    global_max = std::max(global_max, calc_max({ { 1 }, { 1, 1 }, { 0, 1 }}));

    // [][][]
    //   []
    global_max = std::max(global_max, calc_max({ { 1 }, { 1, 1 }, { 1 } }));
    global_max = std::max(global_max, calc_max({ { 0, 1 }, { 1, 1 }, { 0, 1 } }));
    global_max = std::max(global_max, calc_max({ { 1, 1, 1 }, { 0, 1 } }));
    global_max = std::max(global_max, calc_max({ { 0, 1 }, { 1, 1, 1 } }));

    std::cout << global_max << std::endl;

    return 0;
}