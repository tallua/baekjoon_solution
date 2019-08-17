#include <iostream>
#include <array>

using namespace std;


int main(int argc, char** argv)
{
    int N;
    cin >> N;

    array<int, 1001> buffer;

    for(int n = 1; n < N + 1; ++n)
    {
        int val;
        cin >> val;

        buffer[n] = val;
    }

    int inc_val_size = 0;
    array<int, 1001> inc_val;
    array<int, 1001> inc_count;
    inc_val.fill(0);
    for(int n = 1; n < N + 1; ++n)
    {
        int val = buffer[n];

        for(int index = inc_val_size; index >= 0; --index)
        {
            if(inc_val[index] < val)
            {
                inc_val[index + 1] = val;
                if(index + 1 > inc_val_size)
                    inc_val_size = index + 1;
                
                break;
            }
        }

        inc_count[n] = inc_val_size;
    }


    int dec_val_size = 0;
    array<int, 1001> dec_val;
    array<int, 1001> dec_count;
    dec_val.fill(0);
    for(int n = N; n > 0; --n)
    {
        int val = buffer[n];

        for(int index = dec_val_size; index >= 0; --index)
        {
            if(dec_val[index] < val)
            {
                dec_val[index + 1] = val;
                if(index + 1 > dec_val_size)
                    dec_val_size = index + 1;
                
                break;
            }
        }

        dec_count[n] = dec_val_size;
    }

    int max = 0;
    for(int n = 1; n < N + 1; ++n)
    {
        if(dec_count[n] + inc_count[n] - 1 > max)
            max = dec_count[n] + inc_count[n] - 1;
    }
    cout << max << '\n';

    return 0;
}