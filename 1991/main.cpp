#include <iostream>
#include <utility>
#include <array>

using namespace std;

array<pair<size_t, size_t>, 26> nodes;
const size_t root_node = 0;
const size_t null_node = 27;

void print_pre(size_t node)
{
    cout << (char)(node + 'A');
    if(nodes[node].first != null_node)
        print_pre(nodes[node].first);
    if(nodes[node].second != null_node)
        print_pre(nodes[node].second);
}
void print_in(size_t node)
{
    if(nodes[node].first != null_node)
        print_in(nodes[node].first);
    cout << (char)(node + 'A');
    if(nodes[node].second != null_node)
        print_in(nodes[node].second);
}
void print_post(size_t node)
{
    if(nodes[node].first != null_node)
        print_post(nodes[node].first);
    if(nodes[node].second != null_node)
        print_post(nodes[node].second);
    cout << (char)(node + 'A');
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    for(int n = 0; n < N; ++n)
    {
        char p_char, l_char, r_char;
        cin >> p_char >> l_char >> r_char;

        size_t p = p_char - 'A';
        size_t l = l_char == '.' ? null_node : l_char - 'A';
        size_t r = r_char == '.' ? null_node : r_char - 'A';

        nodes[p] = make_pair(l, r);
    }

    print_pre(root_node);
    cout << '\n';
    print_in(root_node);
    cout << '\n';
    print_post(root_node);
    cout << '\n';

    return 0;
}