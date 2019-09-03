#include <iostream>
#include <vector>

using namespace std;

using count_t = size_t;


count_t max_links(const vector<int>& links)
{
    vector<int> refers;
    refers.push_back(-1);

    count_t count_now = 0;
    for(size_t start = 0; start < links.size(); ++start)
    {
        if(links[start] == -1)
        {
            // skip
            continue;
        }

        if(refers.size() == 0)
        {
            refers.push_back(links[start]);
        } 
        else if(refers.back() < links[start])
        {
            refers.push_back(links[start]);
        }
        else
        {
            size_t indx = refers.size() - 2;
            do {
                if(refers[indx] < links[start])
                {
                    refers[indx + 1] = links[start];
                    break;
                }
                else
                {
                    indx--;   
                }
                
            } while(true);
        }
    }

    return refers.size() - 1;
}

int main(int argc, char** argv)
{
    vector<int> links;
    links.resize(501, -1);

    size_t N;
    cin >> N;

    for(size_t n = 0; n < N; ++n)
    {
        size_t l1, l2;
        cin >> l1 >> l2;

        links[l1] = l2;
    }

    cout << (N - max_links(links)) << '\n';


    return 0;
}