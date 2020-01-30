#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TrieNode
{
    size_t next[10] = { 0, };
    bool end = false;
};

int main(int argc, char** argv)
{

    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        vector<TrieNode> trie;
        trie.reserve(55555);
        trie.push_back(TrieNode());

        bool unique = true;
        while (N--)
        {
            string phone_number;
            cin >> phone_number;

            bool new_node = true;
            size_t trie_index = 0;
            size_t phone_index = 0;


            if (unique)
            {
                // insert
                do {
                    // query number shorter than phone_number
                    if (trie[trie_index].end == true)
                    {
                        unique = false;
                        break;
                    }

                    // insert if node not exist
                    const size_t current = phone_number[phone_index] - '0';
                    if (trie[trie_index].next[current] == 0)
                    {
                        trie[trie_index].next[current] = trie.size();
                        trie.push_back(TrieNode());
                    }

                    phone_index++;
                    trie_index = trie[trie_index].next[current];
                } while (phone_index != phone_number.size());

                // query number longer than phone_number
                for (size_t i = 0; i < 10; ++i)
                {
                    if (trie[trie_index].next[i] != 0)
                    {
                        unique = false;
                        break;
                    }
                }

                // check end
                trie[trie_index].end = true;
            }
        }


        if (unique)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}