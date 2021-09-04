#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto read_line = [](auto& is) {
        std::string result;
        std::getline(is, result);
        return result;
    };
    const auto full_text = read_line(std::cin);
    const auto match_text = read_line(std::cin);
    assert(full_text.size() != 0 && match_text.size() != 0);

    const auto kmp_table = [&match_text]() {
        std::vector<int> result(match_text.size() + 1);
        result[0] = -1;

        int candidate_index = 0;
        for (auto n{1}; n < match_text.size(); ++n) {
            if (match_text[candidate_index] == match_text[n]) {
                result[n] = result[candidate_index];
            } else {
                result[n] = candidate_index;
                while (candidate_index >= 0 && match_text[candidate_index] != match_text[n]) {
                    candidate_index = result[candidate_index];
                }
            }
            candidate_index++;
        }
        result[match_text.size()] = candidate_index;

        return result;
    }();

    std::vector<int> match_result;
    int match_index = 0;
    for (auto full_it = full_text.begin(); full_it != full_text.end();) {
        while (match_index >= 0 && *full_it != match_text[match_index]) {
            match_index = kmp_table[match_index];
        }
        match_index++;

        if (match_index == match_text.size()) {
            match_result.push_back(std::distance(full_text.begin(), full_it) - match_text.size() + 2);
            match_index = kmp_table[match_text.size()];
        }
        full_it++;
    }

    std::cout << match_result.size() << '\n';
    std::ranges::for_each(match_result, [](auto val) { std::cout << val << ' '; });

    return 0;
}
