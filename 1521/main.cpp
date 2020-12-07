#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

using encode_t = size_t;
using precision_t = double;
using count_t = size_t;

encode_t encode(const vector<size_t>& numbers)
{
    encode_t result = 0;
    
    for(size_t i = 0; i < numbers.size(); ++i)
    {
        result |= (numbers[i] << (4 * i));
    }

    return result;
}

bool swappable(encode_t encoded, size_t i, size_t j)
{
    encode_t lhs = (encoded & (0x0000000F << (4 * i))) >> 4 * i;
    encode_t rhs = (encoded & (0x0000000F << (4 * j))) >> 4 * j;

    return lhs > rhs;
}

encode_t swap_encode(encode_t encoded, size_t i, size_t j)
{
    encode_t lhs = (encoded & (0x0000000F << (4 * i))) >> 4 * i;
    encode_t rhs = (encoded & (0x0000000F << (4 * j))) >> 4 * j;
    encode_t mask = ~((0x0000000F << (4 * i)) | (0x0000000F << (4 * j)));
    encoded &= mask;
    encoded |= (lhs << (4 * j));
    encoded |= (rhs << (4 * i));

    return encoded;
}

precision_t solve(size_t N, encode_t encoded, map<encode_t, precision_t>& cache)
{
    auto c_it = cache.find(encoded);
    if(c_it != cache.end())
        return c_it->second;

    size_t count = 0;
    precision_t rate = 0.0;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = i + 1; j < N; ++j)
        {
            if(swappable(encoded, i, j))
            {
                auto next = swap_encode(encoded, i, j);
                auto tmp = solve(N, next, cache);
                rate += tmp + 1;
                count += 1;
            }
        }
    }

    const precision_t result = rate / count;
    cache.insert({ encoded, result });
    return result;
}

int main(int argc, char** argv)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    map<encode_t, precision_t> cache;
    {
        vector<size_t> tmp(N);
        for(size_t i = 0; i < N; ++i)
        {
            tmp[i] = i + 1;
        }
        cache.insert({ encode(tmp), 0 });
    }

    vector<size_t> numbers(N);
    for(size_t i = 0; i < N; ++i)
    {
        cin >> numbers[i];
    }

    const auto encoded = encode(numbers);
    const auto result = solve(N, encoded, cache);

    cout << fixed << setprecision(15) << result << endl;

    return 0;
}