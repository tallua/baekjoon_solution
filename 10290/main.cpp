#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

bool is_pelindrom(const std::string& str) {
    auto it = str.begin();
    auto rit = str.rbegin();
    for (; it != str.end(); ++it, ++rit) {
        if (*it != *rit) {
            return false;
        }
    }

    return true;
}

using Marked = std::vector<std::vector<bool>>;
using axis_t = char;

struct Coord {
    axis_t x, y;
};

enum class Direction {
    None,
    Up,
    UpRight,
    Right,
    DownRight,
    Down,
    DownLeft,
    Left,
    UpLeft
};

Coord delta_of(Direction dir) {
    switch (dir) {
        case Direction::Up:
            return {0, -1};
        case Direction::UpRight:
            return {1, -1};
        case Direction::Right:
            return {1, 0};
        case Direction::DownRight:
            return {1, 1};
        case Direction::Down:
            return {0, 1};
        case Direction::DownLeft:
            return {-1, 1};
        case Direction::Left:
            return {-1, 0};
        case Direction::UpLeft:
            return {-1, -1};
    }

    assert("non reachable");
    return {0, 0};
}

struct CoordIterator {
    CoordIterator(Coord coord, Direction dir)
        : coord(coord), delta(delta_of(dir)) {}

    Coord* operator->() { return &coord; }
    Coord& operator*() { return coord; }

    CoordIterator& operator++() {
        coord.x += delta.x;
        coord.y += delta.y;
        return *this;
    }

    Coord coord;
    Coord delta;
};

struct Distance {
    Direction dir;
    axis_t length;
};

//   0 1 2
// 0 x x x
// 1 x * x
// 2 x x x
Distance calc_distance(Coord from, Coord to) {
    if (from.x == to.x && to.y < from.y) {
        return {Direction::Up, axis_t(from.y - to.y + 1)};
    }
    if (from.x + from.y == to.x + to.y && to.y < from.y) {
        return {Direction::UpRight, axis_t(from.y - to.y + 1)};
    }
    if (from.y == to.y && from.x < to.x) {
        return {Direction::Right, axis_t(to.x - from.x + 1)};
    }
    if (from.x - from.y == to.x - to.y && from.y < to.y) {
        return {Direction::DownRight, axis_t(to.y - from.y + 1)};
    }
    if (from.x == to.x && to.y > from.y) {
        return {Direction::Down, axis_t(to.y - from.y + 1)};
    }
    if (from.x + from.y == to.x + to.y && to.y > from.y) {
        return {Direction::DownLeft, axis_t(to.y - from.y + 1)};
    }
    if (from.y == to.y && from.x > to.x) {
        return {Direction::Left, axis_t(from.x - to.x + 1)};
    }
    if (from.x - from.y == to.x - to.y && from.y > to.y) {
        return {Direction::UpLeft, axis_t(from.y - to.y + 1)};
    }
    if (from.x == to.x && from.y == to.y) {
        return {Direction::Up, axis_t(1)};
    }

    return {Direction::None, 0};
}

struct Board {
    Board(std::size_t w, std::size_t h)
        : data(h, std::vector<char>(w)),
          marks(h, std::vector<bool>(w, false)) {}

    char operator[](Coord coord) const { return data[coord.y][coord.x]; }
    char& operator[](Coord coord) { return data[coord.y][coord.x]; }

    const std::vector<Coord>& find(char ch) const {
        assert('A' <= ch && ch <= 'Z');
        return coords[ch - 'A'];
    }

    void mark(Coord coord, Direction dir, std::size_t len) {
        auto coord_it = CoordIterator(coord, dir);

        for (auto i = std::size_t(); i < len; ++i, ++coord_it) {
            marks[coord_it->y][coord_it->x] = true;
        }
    }

    bool is_marked(Coord coord) const { return marks[coord.y][coord.x]; }

    void set_ch(Coord coord, char ch) {
        assert('A' <= ch && ch <= 'Z');
        data[coord.y][coord.x] = ch;
        coords[ch - 'A'].push_back(coord);
    }

    std::size_t h() const { return data.size(); }
    std::size_t w() const { return data[0].size(); }

private:
    std::vector<std::vector<char>> data;
    std::vector<std::vector<bool>> marks;
    std::array<std::vector<Coord>, 26> coords;
};

std::istream& operator>>(std::istream& is, Board& board) {
    for (auto h = axis_t(); h < board.h(); ++h) {
        for (auto w = axis_t(); w < board.w(); ++w) {
            char ch;
            is >> ch;
            board.set_ch({w, h}, ch);
        }
    }

    return is;
}

void run_test(std::istream& is, std::ostream& os) {
    std::size_t n, h, w;
    is >> n >> h >> w;

    auto word_board = [&] {
        Board board(w, h);
        is >> board;
        return board;
    }();

    const auto word_list = [&] {
        std::vector<std::string> list(n);
        for (std::size_t i = 0; i < n; ++i) {
            is >> list[i];
        }
        return list;
    }();

    auto match = [&](const std::string& str, Coord coord,
                     Direction dir) -> bool {
        auto coord_it = CoordIterator(coord, dir);

        for (auto ch : str) {
            if (word_board[*coord_it] != ch) {
                return false;
            }

            ++coord_it;
        }

        return true;
    };

    std::vector<std::size_t> found_counts;
    found_counts.reserve(word_list.size());
    for (auto& word : word_list) {
        std::size_t found_count = 0;

        auto& front_coords = word_board.find(word.front());
        auto& back_coords = word_board.find(word.back());

        for (auto& front : front_coords) {
            for (auto& back : back_coords) {
                const auto dist = calc_distance(front, back);
                if (dist.dir == Direction::None || dist.length != word.size()) {
                    continue;
                }

                if (!match(word, front, dist.dir)) {
                    continue;
                }

                found_count++;
                word_board.mark(front, dist.dir, word.size());
            }
        }

        if (is_pelindrom(word) && word.size() != 1) {
            found_count /= 2;
        }
        found_counts.push_back(found_count);
    }

    if (*std::min_element(found_counts.begin(), found_counts.end()) == 0) {
        os << "no solution";
        return;
    }
    if (*std::max_element(found_counts.begin(), found_counts.end()) > 1) {
        os << "ambiguous";
        return;
    }

    bool word_printed = false;
    for (auto y = char(0); y < h; ++y) {
        for (auto x = char(0); x < w; ++x) {
            if (!word_board.is_marked({x, y})) {
                os << word_board[{x, y}];
                word_printed = true;
            }
        }
    }

    if (!word_printed) {
        os << "empty solution";
        return;
    }
}

#ifndef TEST_ENABLED
int main(int argc, char** argv) {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::size_t T;
    std::cin >> T;

    while (T--) {
        run_test(std::cin, std::cout);
        std::cout << '\n';
    }

    return 0;
}
#endif