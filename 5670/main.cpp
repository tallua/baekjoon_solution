#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>

using namespace std;

struct TrieNode
{
    char count = 0;
    size_t next[26];

    TrieNode() : count(0), next{ 0, } { }
};

void insert_trie(vector<TrieNode>& trie, const size_t trie_indx, const string& str, const size_t indx)
{
    if (indx == str.size())
    {
        trie[trie_indx].count++;
        return;
    }

    if (trie[trie_indx].next[str[indx] - 'a'] == 0)
    {

        trie[trie_indx].next[str[indx] - 'a'] = trie.size();
        trie.emplace_back();
        trie[trie_indx].count++;
    }

    insert_trie(trie, trie[trie_indx].next[str[indx] - 'a'], str, indx + 1);
}

void query_trie(size_t& sum, const vector<TrieNode>& trie, const size_t trie_indx, const string& str, const size_t str_indx)
{
    if (str_indx == str.size())
        return;

    const TrieNode& current = trie[trie_indx];
    if (current.count > 1)
        ++sum;

    query_trie(sum, trie, current.next[str[str_indx] - 'a'], str, str_indx + 1);
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    cout << std::fixed;

    vector<TrieNode> trie;
    vector<string> inputs;

    size_t N;
    while (cin >> N)
    {
        trie.clear();
        trie.reserve(26);
        trie.emplace_back();
        trie[0].count++;

        inputs.resize(N);
        for (size_t i = 0; i < N; ++i)
        {
            cin >> inputs[i];
        }

        for (size_t i = 0; i < N; ++i)
        {
            insert_trie(trie, 0, inputs[i], 0);
        }

        size_t result = 0;
        for (size_t i = 0; i < N; ++i)
        {
            query_trie(result, trie, 0, inputs[i], 0);
        }

        double avg = (double)result / N;
        cout << setprecision(2) << avg << '\n';
    }

    return 0;
}