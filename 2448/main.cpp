#include <iostream>
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

template <size_t K>
void gen_frame(char* const str, const size_t str_w, const size_t frame_x)
{
    constexpr auto prev_offset_x = 3 * pow<2>(K - 1);
    auto prev_x = prev_offset_x + frame_x;

    constexpr auto cur_w = 3 * pow<2>(K + 1);
    constexpr auto cur_h = 3 * pow<2>(K);
    constexpr auto mid_x = 3 * pow<2>(K);
    constexpr auto mid_y = 3 * pow<2>(K - 1);

    gen_frame<K - 1>(str, str_w, prev_x);

    for (size_t y = mid_y; y < cur_h; ++y)
    {
        memset(str + str_w * y, ' ', str_w);
        for (size_t x = frame_x; x < frame_x + cur_w; ++x)
        {
            str[y * str_w + x] = str[(y - mid_y) * str_w + (x % mid_x) + prev_x];
        }
    }
}

template <>
void gen_frame<0>(char* const str, const size_t str_w, const size_t frame_x)
{
    memset(str + str_w * 0, ' ', str_w);
    memset(str + str_w * 1, ' ', str_w);
    memset(str + str_w * 2, ' ', str_w);

    memcpy(str + str_w * 0 + frame_x, "  *   ", 6);
    memcpy(str + str_w * 1 + frame_x, " * *  ", 6);
    memcpy(str + str_w * 2 + frame_x, "***** ", 6);
}

char result[3 * pow<2>(11) * 3 * pow<2>(10)];

template <size_t K>
void print_string()
{
    constexpr auto result_x = 3 * pow<2>(K + 1);
    constexpr auto result_y = 3 * pow<2>(K);

    gen_frame<K>(result, result_x, 0);

    for (int y = 1; y < result_y; ++y)
        result[y * result_x - 1] = '\n';
    result[result_y * result_x - 1] = 0;

    cout << result << '\n';
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

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
