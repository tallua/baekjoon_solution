#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>

using namespace std;

using val_t = size_t;

int main(int argc, char** argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    val_t target;
    size_t cnt;
    cin >> target >> cnt;

    val_t value_max = 0;
    vector<val_t> values;
    values.resize(cnt);
    for(size_t i = 0; i < cnt; ++i) {
        cin >> values[i];

        value_max = max(value_max, values[i]);
    }

    vector<array<val_t, 2>> count_map;
    count_map.resize(value_max * 2, { 0, 0 });
    for(size_t i = 0; i < values.size(); ++i) {
        for(size_t j = i + 1; j < values.size(); ++j) {
            const val_t sum = values[i] + values[j];

            if(count_map[sum][0] == 0) {
                count_map[sum][0] = values[i];
            } else {
                count_map[sum][1] = values[i];
            }
        }
    }

    auto match = [](val_t t1, val_t t2, val_t val1, val_t val2) -> bool {
        if(val1 == 0 || val2 == 0)
            return false;

        val_t val3 = t1 - val1;
        val_t val4 = t2 - val2;

        if(val1 == val2)
            return false;
        if(val1 == val4)
            return false;
        if(val3 == val2)
            return false;
        if(val3 == val4)
            return false;
        return true;
    };

    bool found = false;
    size_t min_i = target > (value_max * 2) ? target - (value_max * 2) : 0;
    for(size_t i = min_i; i < target / 2; ++i) {
        if(count_map[i][0] == 0 || count_map[target - i][0] == 0) {
            continue;
        }

        if(match(i, target - i, count_map[i][0], count_map[target - i][0])) {
            found = true;
            break;
        }

        if(match(i, target - i, count_map[i][0], count_map[target - i][1])) {
            found = true;
            break;
        }
        if(match(i, target - i, count_map[i][1], count_map[target - i][0])) {
            found = true;
            break;
        }
        if(match(i, target - i, count_map[i][1], count_map[target - i][1])) {
            found = true;
            break;
        }
    }

    if(found) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}