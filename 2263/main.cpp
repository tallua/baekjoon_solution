#include <iostream>
#include <array>

using namespace std;

array<size_t, 100000> inorder;
array<size_t, 100000> postorder;
array<size_t, 100001> in_pos;

// [index1, index2)
void parse_range(size_t in_1, size_t in_2, size_t post_1, size_t post_2)
{
    size_t val_mid = postorder[post_2 - 1];
    size_t in_mid = in_pos[val_mid];

    size_t post_sep = post_1 + (in_mid - in_1);

    // preorder print
    cout << val_mid;

    // left subtree
    // [in_1, in_mid) in inorder
    // [post_1, post_sep) in post order
    if(in_1 < in_mid)
    {
        cout << ' ';
        parse_range(in_1, in_mid, post_1, post_sep);
    }
    // right subtree
    // [in_mid + 1, in_2) in inorder
    // [post_sep, post_2 - 1) -> right
    if(in_mid + 1 < in_2)
    {
        cout << ' ';
        parse_range(in_mid + 1, in_2, post_sep, post_2 - 1);
    }
    
}


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    for(int n = 0; n < N; ++n)
    {
        int tmp;
        cin >> tmp;
        inorder[n] = tmp;
        in_pos[tmp] = n;
    }
    for(int n = 0; n < N; ++n)
    {
        int tmp;
        cin >> tmp;
        postorder[n] = tmp;
    }

    parse_range(0, N, 0, N);
    cout << '\n';

    return 0;
}