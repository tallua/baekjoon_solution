#include <iostream>
#include <array>
#include <vector>

using namespace std;

struct BST
{
    struct Node
    {
        int val;
        size_t left;
        size_t right;
    };

    const size_t _root = 0;
    const size_t _null = 1 << 31;
    vector<Node> _nodes;

    BST()
    {
        _nodes.reserve(10000);
    }

    size_t size() const 
    { 
        return _nodes.size(); 
    }

    void insert(int val)
    {
        if(_nodes.size() == 0)
        {
            _nodes.push_back({val, _null, _null});
        }
        else
        {
            size_t chk = _root;
            
            while(true)
            {
                 
                if(val < _nodes[chk].val)
                {
                    // insert left
                    if(_nodes[chk].left == _null)
                    {
                        size_t now = _nodes.size();
                        _nodes[chk].left = now;
                        _nodes.push_back({val, _null, _null});
                        break;
                    }
                    else
                    {
                        chk = _nodes[chk].left;
                    }
                }
                else
                {
                    // insert right
                    if(_nodes[chk].right == _null)
                    {
                        size_t now = _nodes.size();
                        _nodes[chk].right = now;
                        _nodes.push_back({val, _null, _null});
                        break;
                    }
                    else
                    {
                        chk = _nodes[chk].right;
                    }
                }
                
            }
        }
    }

    void print_post(size_t node)
    {
        if(_nodes[node].left != _null)
            print_post(_nodes[node].left);
        if(_nodes[node].right != _null)
            print_post(_nodes[node].right);
        cout << _nodes[node].val << endl;
    }
};



int main(int argc, char** argv)
{
    BST tree;

    int x;
    while(cin >> x)
    {
        tree.insert(x);
    }

    tree.print_post(tree._root);

    return 0;
}