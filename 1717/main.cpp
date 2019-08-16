#include <iostream>
#include <array>
#include <unordered_set>
#include <memory>

using namespace std;

static size_t NextId = 0;
struct RefSet;

struct RefSet
{
    size_t id;
    unordered_set<size_t> set;
    shared_ptr<RefSet> parent;

    RefSet()
    {
        id = NextId++;
        parent = nullptr;
    }

    bool merge(std::shared_ptr<RefSet> other)
    {
        if(other->getId() == getId())
            return false;
        
        if(set.size() < 100 && other->set.size() < 100)
        {
            // merge to other
            
            return true;
        }
        else
        {
            parent = other;
            return false;
        }
        
    }

    size_t getId()
    {
        if(parent)
            return parent->getId();
        return id;
    }
};

struct MySets
{
    

    void join(size_t a, size_t b)
    {

    }

    void clean(size_t N)
    {

    }

    bool isSameSet(size_t a, size_t b)
    {

    }
};


/// 0 1 2 3 4 5
/// | | | | | |
/// 2 0 2 3 4 5
// 0 0 1
// 2 2
// 3 3
// 4 4
// 5 5



int main(int argc, char** argv)
{
    int N, M;
    cin >> N >> M;

    MySets myset;

    for(int m = 0; m < M; ++m)
    {
        int op, a, b;
        cin >> op >> a >> b;

        switch(op)
        {
        case 0:
            myset.join(a, b);
            break;
        case 1:
            myset.clean(N);
            bool same = myset.isSameSet(a, b);
            cout << (same ? "YES" : "NO") << '\n';
            break;
        }
    }

    return 0;
}

