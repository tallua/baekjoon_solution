#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;
using hash_t = unsigned long;
using ul = unsigned long long;

const size_t max_hash_size = 17876543;
const hash_t hash_key_unused = 1 << 30;
hash_t hash_key[max_hash_size] = { 0, };
int counter[max_hash_size] = { 0, };

void next_hash(hash_t& val)
{
    val = (((val << 2) + ~val) ^ 0x34567871) % max_hash_size;
}

void assign_key(const int val, hash_t& key)
{
    key = val;

    next_hash(key);
    while (hash_key[key] != hash_key_unused && hash_key[key] != val)
        next_hash(key);

    if (hash_key[key] == hash_key_unused)
        hash_key[key] = val;

    //cout << "assign : " << val << " : " << key << endl;
}

bool find_key(const int val, hash_t& key)
{
    key = val;

    next_hash(key);
    while (hash_key[key] != hash_key_unused && hash_key[key] != val)
        next_hash(key);

    if (hash_key[key] == hash_key_unused || hash_key[key] != val)
        return false;
    return true;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    std::fill_n(hash_key, max_hash_size, hash_key_unused);

    int N;
    cin >> N;

    vector<int> a, b, c, d;
    a.resize(N);
    b.resize(N);
    c.resize(N);
    d.resize(N);

    for (ul i = 0; i < N; ++i)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    for (ul i = 0; i < N; ++i)
    {
        for (ul j = 0; j < N; ++j)
        {
            hash_t key;
            assign_key(a[i] + b[j], key);
            counter[key]++;
        }
    }

    long long answer = 0;
    for (ul i = 0; i < N; ++i)
    {
        for (ul j = 0; j < N; ++j)
        {
            hash_t key;
            bool found = find_key(0 - c[i] - d[j], key);
            if (found)
                answer += counter[key];
        }
    }

    cout << answer << endl;

    return 0;
}