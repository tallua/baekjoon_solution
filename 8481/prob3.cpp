#include <iostream>

using namespace std;

void p3_1(size_t n, size_t t, size_t f)
{
    if (n == 4)
    {
        size_t type = f % 4;
        if (type == 0) cout << "****";
        if (type == 3) cout << "*.*";
        if (type == 2) cout << "**";
        if (type == 1) cout << "*";
    }
    else
    {
        size_t h = n / 2;
        if (f > h)
        {
            p3_1(h, h, f - h);
            for (auto i = f - h; i < h; ++i) cout << ".";
            p3_1(h, t - h, f - h);
        }
        else
        {
            p3_1(h, h, f);
        }
    }
}

void p3()
{
    const size_t p3l = 1024;
    const size_t h = p3l / 2;
    for (size_t l = 0; l < h; ++l)
    {
        p3_1(p3l, p3l - l, p3l - l);
        cout << endl;
    }
    for (size_t l = 0; l < h; ++l)
    {
        p3_1(h, h - l, h - l);
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    p3();
    return 0;
}