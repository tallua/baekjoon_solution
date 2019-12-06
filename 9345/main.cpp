#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DVDLack
{
private:
    struct segment_
    {
        int min_val, max_val;
        bool dirty;
    };

    vector<vector<segment_>> segments_;
    vector<int> dvds_;

public:
    DVDLack(int size)
    {
        dvds_.resize(size);
        for (int i = 0; i < size; ++i)
            dvds_[i] = i;

        // build segtree
        int N = size;
        int mult = 1;
        do
        {
            vector<segment_> segment_list;
            segment_list.resize(N);
            for(int i = 0; i < N; ++i)
            {
                segment_list[i].min_val = i * mult;
                segment_list[i].max_val = (i + 1) * mult - 1;
                segment_list[i].dirty = false;
            }
            segments_.push_back(segment_list);

            mult = mult * 2;
            N = N / 2;
        } while (N > 0);
    }

    void swap(int index1, int index2)
    {
        if(index1 == index2)
            return;

        std::swap(dvds_[index1], dvds_[index2]);
        raise_dirty_(index1);
        raise_dirty_(index2);
    }

    // [index1, index2]
    bool check(int index1, int index2)
    {
        return check_(index1, index2, 0, index1, index2);
    }

private:
    // [L, R]
    // [range1, range2]
    bool check_(const int L, const int R, int height, int index1, int index2)
    {
        if(index1 == index2)
        {
            resolve_dirty_(height, index1);
            if(segments_[height][index1].min_val < L)
                return false;
            if(segments_[height][index1].max_val > R)
                return false;
            return true;
        }

        if(index1 % 2 == 1)
        {
            // check index1
            resolve_dirty_(height, index1);
            if(segments_[height][index1].min_val < L)
                return false;
            if(segments_[height][index1].max_val > R)
                return false;

            index1++;
        }

        if(index2 % 2 == 0)
        {
            // check index2
            resolve_dirty_(height, index2);
            if(segments_[height][index2].min_val < L)
                return false;
            if(segments_[height][index2].max_val > R)
                return false;

            index2--;
        }

        if(index1 > index2)
        {
            return true;
        }

        // check at higher
        bool mid = check_(L, R, height + 1, index1 / 2, index2 / 2);

        return mid;
    }

    void resolve_dirty_(int height, int index)
    {
        if(!segments_[height][index].dirty)
            return;
        
        if(height == 0)
        {
            segments_[height][index].min_val = dvds_[index];
            segments_[height][index].max_val = dvds_[index];
        }
        else
        {
            resolve_dirty_(height - 1, index * 2);
            resolve_dirty_(height - 1, index * 2 + 1);

            segments_[height][index].min_val = std::min(
                segments_[height - 1][index * 2].min_val, 
                segments_[height - 1][index * 2 + 1].min_val);
            segments_[height][index].max_val =  std::max(
                segments_[height - 1][index * 2].max_val, 
                segments_[height - 1][index * 2 + 1].max_val);
        }

        segments_[height][index].dirty = false;
    }

    void raise_dirty_(int index)
    {
        int height = 0;
        do {
            segments_[height][index].dirty = true;

            if(index % 2 == 0 && index == segments_[height].size() - 1)
            {
                // break if no higher segment
                break;
            }

            height++;
            index = index / 2;
        } while(height < segments_.size());
    }
};

void test_case()
{
    int N, K;
    cin >> N >> K;

    DVDLack lack(N);

    for (int k = 0; k < K; ++k)
    {
        int op, A, B;
        cin >> op >> A >> B;

        switch (op)
        {
        case 0:
            lack.swap(A, B);
            break;
        case 1:
            cout << (lack.check(A, B) ? "YES\n" : "NO\n");
            break;
        }
    }
}

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t)
    {
        test_case();
    }

    return 0;
}