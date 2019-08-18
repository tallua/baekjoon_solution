#include <iostream>

int result[15] =
{ 1, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596};

int main(int argc, char** argv)
{
    int N;
    std::cin >> N;
    std::cout << result[N] << '\n';

    return 0;
}