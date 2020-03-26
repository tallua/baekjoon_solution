#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;
using coord_t = int;

struct Rect
{
    coord_t x1, x2;
    coord_t y1, y2;
};

struct RectSortX
{
    bool operator () (const Rect& lhs, const Rect& rhs) const
    {
        return lhs.x2 > rhs.x2;
    }
};

coord_t get_height_sum(vector<Rect> rectangles)
{
    if(rectangles.size() == 0)
        return 0;

    sort(rectangles.begin(), rectangles.end(), [&](const Rect& lhs, const Rect& rhs) -> bool {
        return lhs.y1 == rhs.y1 ? lhs.y2 < rhs.y2 : lhs.y1 < rhs.y1;
    });

    coord_t sum = 0;

    coord_t min_y = rectangles[0].y1;
    coord_t max_y = rectangles[0].y2;

    for(const Rect& r : rectangles)
    {
        if(r.y1 > max_y)
        {
            sum += max_y - min_y;
            min_y = r.y1;
            max_y = r.y2;
        }
        else
        {
            max_y = max(max_y, r.y2);
        }
    }

    sum += max_y - min_y;

    return sum;
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    size_t N;
    cin >> N;

    vector<Rect> rectangles;
    vector<coord_t> x_list;
    rectangles.resize(N);

    for(size_t n = 0; n < N; ++n)
    {
        double fx, fy, fw, fh;
        cin >> fx >> fy >> fw >> fh;
        
        coord_t x = (fx + 0.05) * 10;
        coord_t y = (fy + 0.05) * 10;
        coord_t w = (fw + 0.05) * 10;
        coord_t h = (fh + 0.05) * 10;

        rectangles[n].x1 = x;
        rectangles[n].x2 = x + w;
        rectangles[n].y1 = y;
        rectangles[n].y2 = y + h;

        x_list.push_back(x);
        x_list.push_back(x + w);
    }

    x_list.push_back(numeric_limits<coord_t>::min());
    x_list.push_back(numeric_limits<coord_t>::max());

    sort(x_list.begin(), x_list.end());
    sort(rectangles.begin(), rectangles.end(), [](const Rect& lhs, const Rect& rhs) {
        return lhs.x1 < rhs.x1;
    });

    coord_t area_sum = 0;

    vector<Rect> current_set;
    size_t x_index = 0;
    size_t rect_index = 0;
    while(x_index < x_list.size() - 1)
    {
        const coord_t current_x = x_list[x_index];
        const coord_t next_x = x_list[x_index + 1];

        // erase from current set
        while(current_set.size() > 0 && current_set[0].x2 < next_x)
        {
            pop_heap(current_set.begin(), current_set.end(), RectSortX());
            current_set.pop_back();
        }

        // calc heights
        coord_t heights = get_height_sum(current_set);
        //cout << current_x << " ~ " << next_x << " : " << heights << endl;
        //for(auto& r : current_set)
        //{
        //    cout << "    " << r.x1 << ' ' << r.x2 << ' ' << r.y1 << " ~ " << r.y2 << endl;
        //}

        // add to current set
        while(rect_index < rectangles.size() && rectangles[rect_index].x1 <= next_x)
        {
            current_set.push_back(rectangles[rect_index]);
            push_heap(current_set.begin(), current_set.end(), RectSortX());
            rect_index++;
        }

        // add sum
        area_sum += (next_x - current_x) * heights;
        x_index++;
    }
    
    if(area_sum % 100 == 0)
        cout << (area_sum / 100) << endl;
    else
        cout << fixed << setprecision(2) << (area_sum / 100.0) << endl;

    return 0;
}