#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template <int K>
constexpr size_t pow(size_t e)
{
    int result = 1;
    for (int tmp = 0; tmp < e; ++tmp)
        result *= K;
    return result;
}

vector<char*> result;

void gen_result(int k)
{
    if (k < result.size())
        return;
    else if (k < 0)
        return;

    gen_result(k - 1);

    auto cur_x = 3 * pow<2>(k + 1);
    auto cur_y = 3 * pow<2>(k);
    result.push_back(new char[cur_x * cur_y]);

    auto& current = result.back();

    if (k == 0)
    {
        const char* result_0 =
            "  *   "
            " * *  "
            "***** ";
        memcpy(current, result_0, cur_x * cur_y);
    }
    else
    {
        auto low_frame = result[k - 1];

        auto low_x = 3 * pow<2>(k);
        auto low_y = 3 * pow<2>(k - 1);

        for (int y = 0; y < cur_y; ++y)
        {
            if (y < low_y)
            {
                int x = 0;
                for (; x < (low_x / 2); ++x)
                    current[y * cur_x + x] = ' ';
                for (; x < (low_x / 2 * 3); ++x)
                    current[y * cur_x + x] = low_frame[y * low_x + x - (low_x / 2)];
                for (; x < cur_x; ++x)
                    current[y * cur_x + x] = ' ';
            }
            else
            {
                for (int x = 0; x < cur_x; ++x)
                {
                    current[y * cur_x + x] = low_frame[(y - low_y) * low_x + (x % low_x)];
                }
            }
        }
    }
}

void clean()
{
    for(int i = 0; i < result.size(); ++i)
        delete[] result[i];
    result.clear();
}


template <size_t K>
void print_string()
{
    gen_result(K);

    auto& current = result[K];

    auto cur_x = 3 * pow<2>(K + 1);
    auto cur_y = 3 * pow<2>(K);

    for (int y = 1; y < cur_y; ++y)
    {
        current[y * cur_x - 1] = '\n';
    }

    current[cur_y * cur_x - 1] = 0;

    printf("%s\n", current);

    clean();
}

int main(int argc, char** argv)
{
    int n;
    cin >> n;

    switch (n)
    {
    case 3:
        print_string<0>();
        break;                
    case 6:                   
        print_string<1>();
        break;                
    case 12:                  
        print_string<2>();
        break;                
    case 24:                  
        print_string<3>();
        break;                
    case 48:                  
        print_string<4>();
        break;                
    case 96:                  
        print_string<5>();
        break;                
    case 192:                 
        print_string<6>();
        break;                
    case 384:                 
        print_string<7>();
        break;                
    case 768:                 
        print_string<8>();
        break;                
    case 1536:                
        print_string<9>();
        break;                
    case 3072: 
        print_string<10>();
        break;
    }

    return 0;
}
