#include <iostream>
#include <array>
#include <utility>

const size_t CUBE_SIZE = 3;
using namespace std;
using surface_t = array<char, CUBE_SIZE * CUBE_SIZE>;
using loop_t = array<size_t, CUBE_SIZE>;

enum rotation_type
{
    CW,
    CCW
};

enum surface_id
{
    TOP,
    DOWN,
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

const array<array<pair<surface_id, loop_t>, 4>, 6> rot_info = { {
    {{ {BACK, {2, 1, 0}}, {RIGHT, {2, 1, 0}}, {FRONT, {2, 1, 0}}, {LEFT, {2, 1, 0}} }},
    {{ {FRONT, {6, 7, 8}}, {RIGHT, {6, 7, 8}}, {BACK, {6, 7, 8}}, {LEFT, {6, 7, 8}} }},
    {{ {TOP, {6, 7, 8}}, {RIGHT, {0, 3, 6}}, {DOWN, {2, 1, 0}}, {LEFT, {8, 5, 2}} }},
    {{ {TOP, {2, 1, 0}}, {LEFT, {0, 3, 6}}, {DOWN, {6, 7, 8}}, {RIGHT, {8, 5, 2}} }},
    {{ {TOP, {0, 3, 6}}, {FRONT, {0, 3, 6}}, {DOWN, {0, 3, 6}}, {BACK, {8, 5, 2}} }},
    {{ {TOP, {8, 5, 2}}, {BACK, {0, 3, 6}}, {DOWN, {8, 5, 2}}, {FRONT, {8, 5, 2}} }}
} };

//     012
//     3T5
//     678
//
// 012 012 012 012
// 3L5 3F5 3R5 3B5
// 678 678 678 678
//
//     012
//     3D5
//     678

void p_line(const surface_t& surf, int indx)
{
    cout << surf[indx] << surf[indx + 1] << surf[indx + 2] << ' ';
}
void debug_cube(const array<surface_t, 6>& cube)
{
    cout << "    "; p_line(cube[TOP], 0); cout << endl;
    cout << "    "; p_line(cube[TOP], 3); cout << endl;
    cout << "    "; p_line(cube[TOP], 6); cout << endl;
    p_line(cube[LEFT], 0); p_line(cube[FRONT], 0); p_line(cube[RIGHT], 0); p_line(cube[BACK], 0); cout << endl;
    p_line(cube[LEFT], 3); p_line(cube[FRONT], 3); p_line(cube[RIGHT], 3); p_line(cube[BACK], 3); cout << endl;
    p_line(cube[LEFT], 6); p_line(cube[FRONT], 6); p_line(cube[RIGHT], 6); p_line(cube[BACK], 6); cout << endl;
    cout << "    "; p_line(cube[DOWN], 0); cout << endl;
    cout << "    "; p_line(cube[DOWN], 3); cout << endl;
    cout << "    "; p_line(cube[DOWN], 6); cout << endl;
}

void rotate_cube(rotation_type rot_type, surface_t& front,
    surface_t& top, const loop_t& t_loop,
    surface_t& right, const loop_t& r_loop,
    surface_t& down, const loop_t& d_loop,
    surface_t& left, const loop_t& l_loop)
{
    if (rot_type == rotation_type::CW)
    {
        char tmp;
        tmp = front[0];
        front[0] = front[6];
        front[6] = front[8];
        front[8] = front[2];
        front[2] = tmp;
        tmp = front[1];
        front[1] = front[3];
        front[3] = front[7];
        front[7] = front[5];
        front[5] = tmp;

        for (size_t indx = 0; indx < CUBE_SIZE; ++indx)
        {
            char tmp = top[t_loop[indx]];
            top[t_loop[indx]] = left[l_loop[indx]];
            left[l_loop[indx]] = down[d_loop[indx]];
            down[d_loop[indx]] = right[r_loop[indx]];
            right[r_loop[indx]] = tmp;
        }
    }
    else
    {
        char tmp;
        tmp = front[0];
        front[0] = front[2];
        front[2] = front[8];
        front[8] = front[6];
        front[6] = tmp;
        tmp = front[1];
        front[1] = front[5];
        front[5] = front[7];
        front[7] = front[3];
        front[3] = tmp;

        for (size_t indx = 0; indx < CUBE_SIZE; ++indx)
        {
            char tmp = top[t_loop[indx]];
            top[t_loop[indx]] = right[r_loop[indx]];
            right[r_loop[indx]] = down[d_loop[indx]];
            down[d_loop[indx]] = left[l_loop[indx]];
            left[l_loop[indx]] = tmp;
        }
    }
}

inline void rotate_cube(rotation_type rot_type, array<surface_t, 6>& cube, surface_id face)
{
    rotate_cube(rot_type, cube[face],
        cube[rot_info[face][0].first], rot_info[face][0].second,
        cube[rot_info[face][1].first], rot_info[face][1].second,
        cube[rot_info[face][2].first], rot_info[face][2].second,
        cube[rot_info[face][3].first], rot_info[face][3].second);
}

int main(int argc, char** argv)
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--)
    {
        array<surface_t, 6> cube;
        cube[surface_id::TOP].fill('w');
        cube[surface_id::DOWN].fill('y');
        cube[surface_id::FRONT].fill('r');
        cube[surface_id::BACK].fill('o');
        cube[surface_id::LEFT].fill('g');
        cube[surface_id::RIGHT].fill('b');

        int N;
        cin >> N;

        while (N--)
        {
            char face, op;
            cin >> face >> op;

            rotation_type type = op == '-' ? rotation_type::CCW : rotation_type::CW;
            surface_id id = face == 'U' ? surface_id::TOP :
                face == 'D' ? surface_id::DOWN :
                face == 'F' ? surface_id::FRONT :
                face == 'B' ? surface_id::BACK :
                face == 'L' ? surface_id::LEFT :
                surface_id::RIGHT;

            rotate_cube(type, cube, id);
            //debug_cube(cube);
        }

        // print top
        for (size_t i = 0; i < CUBE_SIZE * CUBE_SIZE; ++i)
        {
            cout << cube[TOP][i];
            if (i % CUBE_SIZE == CUBE_SIZE - 1)
                cout << '\n';
        }
    }

    cout << endl;

    return 0;
}
