#include <array>
#include <iostream>

namespace {

template <typename _Tp>
using board_t = std::array<_Tp, 36>;

struct coord_t {
    int x, y;
};

coord_t find_first_one(const board_t<int>& board) {
    for (int x = 0; x < board.size(); ++x) {
        if (board[x] == 1)
            return {x % 6, x / 6};
    }

    return {};
}

bool is_in_board(const coord_t& pos) {
    if (pos.x < 0 || 6 <= pos.x) {
        return false;
    }

    if (pos.y < 0 || 6 <= pos.y) {
        return false;
    }

    return true;
}

//  Up
//  Front Right Back Left
//  Down

enum class Face : int { Front, Right, Up, Down, Left, Back };

enum class Direction : int { Up, Right, Down, Left };

struct Cube {
    std::array<Face, 6> faces;

    const Face& front() const { return faces[0]; }

    Cube move(Direction dir) {
        switch (dir) {
            case Direction::Right: {
                return {
                    faces[1], faces[2], faces[3], faces[0], faces[4], faces[5],
                };
            }
            case Direction::Left: {
                return {
                    faces[3], faces[0], faces[1], faces[2], faces[4], faces[5],
                };
            }
            case Direction::Up: {
                return {faces[5], faces[1], faces[4],
                        faces[3], faces[0], faces[2]};
            }
            case Direction::Down: {
                return {faces[4], faces[1], faces[5],
                        faces[3], faces[2], faces[0]};
            }
        }

        return *this;
    }
};

Cube createInitialCube() {
    return {Face::Front, Face::Right, Face::Back,
            Face::Left,  Face::Down,  Face::Up};
}

auto get_value(const auto& b, coord_t pos) { return b[pos.x + pos.y * 6]; }
void set_value(auto& b, coord_t pos, auto value) {
    b[pos.x + pos.y * 6] = std::move(value);
}

}  // namespace

bool dfs(board_t<int>& board, std::array<bool, 6>& visited, Cube cube, coord_t pos) {
    if (visited[static_cast<int>(cube.front())]) {
        return false;
    }
    visited[static_cast<int>(cube.front())] = true;
    set_value(board, pos, 0);

    auto check = [&](coord_t next, Direction dir) {
        if (is_in_board(next) && get_value(board, next) == 1) {
            return dfs(board, visited, cube.move(dir), next);
        }

        return true;
    };

    if (!check({pos.x - 1, pos.y}, Direction::Left)) {
        return false;
    }
    if (!check({pos.x + 1, pos.y}, Direction::Right)) {
        return false;
    }
    if (!check({pos.x, pos.y - 1}, Direction::Up)) {
        return false;
    }
    if (!check({pos.x, pos.y + 1}, Direction::Down)) {
        return false;
    }

    return true;
}

bool solution(const board_t<int>& board) {
    auto front_pos = find_first_one(board);

    std::array<bool, 6> face_occurence;
    face_occurence.fill(false);

    auto cube = createInitialCube();

    board_t<int> copied_board = board;
    auto result = dfs(copied_board, face_occurence, cube, front_pos);

    return result;
}

#ifndef TEST_ENABLED
int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 0; i < 3; ++i) {
        auto board = [] {
            board_t<int> b;
            for (int j = 0; j < b.size(); ++j) {
                std::cin >> b[j];
            }

            return b;
        }();

        if (solution(board)) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }

    return 0;
}
#endif