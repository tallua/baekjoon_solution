#include <iostream>
#include <array>

int main(int argc, char** argv)
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::array<int, 1000000> arr;
    for(int i = 0; i < N; ++i)
        std::cin >> arr[i];

    int B, C;
    std::cin >> B >> C;

    long long count = 0;
    for(int i = 0; i < N; ++i)
        count += 1 + (arr[i] - B > 0 ? (arr[i] - B) / C + ((arr[i] - B) % C == 0 ? 0 : 1) : 0);
    
    std::cout << count << std::endl;

    return 0;
}
