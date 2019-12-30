#include <iostream>
#include <map>

using namespace std;

long long fp(map<long long, long long>& cache, long long nth)
{
    auto tmp = cache.find(nth);
    if (tmp != cache.end())
        return tmp->second;

    long long k = nth / 2;

    long long fp_k = fp(cache, k);
    long long fp_k_1 = fp(cache, k + 1);

    if (nth % 2 == 0)
    {
        long long tmp = (2ll * fp_k_1) - fp_k;
        if (tmp < 0)
            tmp += 1000000ll;
        cache[nth] = fp_k * tmp;
    }
    else
    {
        cache[nth] = (fp_k_1 * fp_k_1) + (fp_k * fp_k);
    }

    cache[nth] %= 1000000ll;

    return cache[nth];
}


int main(int argc, char** argv)
{
    long long n;
    cin >> n;

    map<long long, long long> cache;
    cache[0] = 0;
    cache[1] = 1;
    cache[2] = 1;
    cache[3] = 2;

    cout << fp(cache, n) << endl;

    return 0;
}