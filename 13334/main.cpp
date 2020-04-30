#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using coord_t = int;

struct LocationInfo
{
    coord_t left;
    coord_t right;
};

struct LeftComapre
{
    bool operator () (const LocationInfo& lhs, const LocationInfo& rhs)
    {
        return lhs.left > rhs.left;
    }
};

struct RightComapre
{
    bool operator () (const LocationInfo& lhs, const LocationInfo& rhs)
    {
        return lhs.right > rhs.right;
    }
};

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    vector<coord_t> coords;
    vector<LocationInfo> locations;
    coords.reserve(N);
    locations.resize(N);
    for(size_t n = 0; n < N; ++n)
    {
        cin >> locations[n].left >> locations[n].right;
        if(locations[n].left > locations[n].right)
        {
            swap(locations[n].left, locations[n].right);
        }

        coords.push_back(locations[n].left);
    }

    coord_t L;
    cin >> L;

    auto left_comp = [&](const size_t& lhs, const size_t& rhs) 
    {
        return locations[lhs].left > locations[rhs].left;
    };
    auto right_comp = [&](const size_t& lhs, const size_t& rhs) 
    {
        return locations[lhs].right > locations[rhs].right;
    };

    sort(coords.begin(), coords.end());



    size_t result = 0;
    size_t insert_index = 0;
    vector<size_t> insert_list;
    priority_queue<size_t, vector<size_t>, decltype(right_comp)> pending(right_comp);
    priority_queue<size_t, vector<size_t>, decltype(left_comp)> current(left_comp);
    
    insert_list.resize(N);
    for(size_t n = 0; n < N; ++n)
    {
        insert_list[n] = n;
    }
    sort(insert_list.begin(), insert_list.end(), [&](const size_t& lhs, const size_t& rhs) 
    {
        return locations[lhs].left < locations[rhs].left;
    });

    for(auto c_it = coords.begin(); c_it != coords.end(); ++c_it)
    {
        const coord_t& current_coord = *c_it;
        const coord_t left_bound = current_coord;
        const coord_t right_bound = current_coord + L;

        while(insert_index < N && locations[insert_list[insert_index]].left <= right_bound)
        {
            size_t top = insert_list[insert_index];
            if(locations[top].right - locations[top].left <= L)
            {
                pending.push(top);
                //cout << "pended : " << top << endl;
            }
            insert_index++;
        }

        while(!pending.empty() && locations[pending.top()].right <= right_bound)
        {
            current.push(pending.top());
            //cout << "pushed : " << pending.top() << endl;
            pending.pop();
        }

        while(!current.empty() && locations[current.top()].left < left_bound)
        {
            //cout << "popped : " << current.top() << endl;
            current.pop();
        }

        //cout << "current : " << current_coord << " = " << current.size() << endl;
        result = max(result, current.size());
    }
    
    std::cout << result << endl;

    return 0;
}