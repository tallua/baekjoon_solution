#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>

using namespace std;

const size_t MAX_PRIME_NUMBER = 2001;
array<bool, MAX_PRIME_NUMBER> is_prime_number;
bool is_prime_number_cached = false;

void cache_prime()
{
    is_prime_number.fill(true);
    is_prime_number[0] = false;
    is_prime_number[1] = false;

    for (size_t i = 2; i < MAX_PRIME_NUMBER; ++i)
    {
        if (is_prime_number[i])
        {
            for (size_t n = i * 2; n < MAX_PRIME_NUMBER; n += i)
            {
                is_prime_number[n] = false;
            }
        }
    }
}

bool is_prime(size_t number)
{
    return is_prime_number[number];
}


const size_t invalid = numeric_limits<size_t>::max();

bool bipartite(const vector<size_t>& from, const vector<size_t>& to, vector<size_t>& match, vector<bool>& visited, size_t index)
{
    for (size_t n = 0; n < to.size(); ++n)
    {
        if (is_prime(from[index] + to[n]) && !visited[n])
        {
            visited[n] = true;

            if (match[n] == invalid || bipartite(from, to, match, visited, match[n]))
            {
                match[n] = index;
                return true;
            }
        }
    }

    return false;
}

bool try_match(const vector<size_t>& from, const vector<size_t>& to, size_t except)
{

    vector<size_t> match;
    match.resize(to.size(), invalid);
    for (size_t f = 0; f < from.size(); ++f)
    {
        vector<bool> visited;
        visited.resize(to.size(), false);
        visited[except] = true;

        if (!bipartite(from, to, match, visited, f))
            return false;
    }

    return true;
}



int main(int argc, char** argv)
{
    cache_prime();

    // get input
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    size_t N;
    cin >> N;

    size_t first_number = invalid;
    vector<size_t> even_numbers;
    even_numbers.reserve(N);
    vector<size_t> odd_numbers;
    odd_numbers.reserve(N);
    for (size_t n = 0; n < N; ++n)
    {
        size_t number;
        cin >> number;
        if (first_number == invalid)
            first_number = number;
        else if (number % 2 == 0)
            even_numbers.push_back(number);
        else
            odd_numbers.push_back(number);
    }

    // try match
    bool can_match = true;
    if (even_numbers.size() != odd_numbers.size())
        can_match = false;

    vector<size_t> answers;
    answers.reserve(N);
    if (first_number % 2 == 0 && even_numbers.size() + 1 == odd_numbers.size())
    {
        for (size_t n = 0; n < odd_numbers.size(); ++n)
        {
            if (is_prime(first_number + odd_numbers[n]) &&
                try_match(even_numbers, odd_numbers, n))
            {
                answers.push_back(odd_numbers[n]);
            }
        }
    }
    else if (first_number % 2 == 1 && even_numbers.size() == odd_numbers.size() + 1)
    {
        for (size_t n = 0; n < even_numbers.size(); ++n)
        {
            if (is_prime(first_number + even_numbers[n]) &&
                try_match(odd_numbers, even_numbers, n))
            {
                answers.push_back(even_numbers[n]);
            }
        }
    }

    // print
    if (answers.size() == 0)
    {
        cout << "-1\n";
    }
    else
    {
        sort(answers.begin(), answers.end());
        for (size_t a = 0; a < answers.size(); ++a)
            cout << answers[a] << ' ';
        cout << '\n';
    }

    cout << endl;

    return 0;
}