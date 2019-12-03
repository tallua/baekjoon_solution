#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    for(int t = 0; t < T; ++t)
    {
        int N, M;
        cin >> N >> M;

        int target_priority = -1;
        vector<vector<int>> docs;
        docs.resize(10);
        for(int n = 0; n < N; ++n)
        {
            int priority;
            cin >> priority;

            if(n == M)
                target_priority = priority;
            docs[priority].push_back(n);
        }

        // back iterate
        int count = 0;
        int head = 0;
        for(int priority = 9; priority > target_priority; -- priority)
        {
            if(docs[priority].size() == 0)
                continue;

            // find next document after head
            auto next = std::find_if(docs[priority].begin(), docs[priority].end(), 
                [&](int val) { return head <= val; });
            if(next == docs[priority].end())
                next = docs[priority].begin();

            // head will end last document
            if(next == docs[priority].begin())
                head = *(docs[priority].end() - 1);
            else
                head = *(next - 1);

            count += docs[priority].size();
        }

        // forward iterate from head
        auto next = std::find_if(docs[target_priority].begin(), docs[target_priority].end(), 
            [&](int val) { return head <= val; });
        if(next == docs[target_priority].end())
            next = docs[target_priority].begin();

        while(*next != M)
        {
            next++;
            count++;
            if(next == docs[target_priority].end())
                next = docs[target_priority].begin();
        }

        cout << (count + 1) << '\n';
    }

    return 0;
}

