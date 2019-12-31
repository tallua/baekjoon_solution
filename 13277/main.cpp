#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

template <typename T>
constexpr T unit_pow(T base, int exp)
{
    T result = 1;
    for (int i = 0; i < exp; ++i)
    {
        result *= base;
    }

    return result;
}

struct BigInteger
{
private:
    using unit_type = long long;
    const int unit_size = 7;
    const unit_type unit_size_val = unit_pow(10, unit_size);

    bool positive;
    vector<unit_type> blocks;

    BigInteger(vector<unit_type>::iterator begin, vector<unit_type>::iterator end, bool positive)
        : positive(positive)
    {
        blocks.reserve(std::distance(begin, end));
        for(auto it = begin; it != end; ++it)
        {
            blocks.push_back(*it);
        }
    }

public:
    BigInteger(std::string val_str)
    {
        positive = true;
        if (val_str[0] == '-')
        {
            positive = false;
            val_str = val_str.substr(1);
        }

        int offset = val_str.size() % unit_size;
        int block_count = val_str.size() / unit_size;

        for (int i = block_count; i > 0; --i)
        {
            unit_type block = parse(val_str.substr(offset + (i - 1) * unit_size, unit_size));
            blocks.push_back(block);
        }

        if (offset != 0)
        {
            unit_type block = parse(val_str.substr(0, offset));
            blocks.push_back(block);
        }
    }

    unit_type parse(const std::string &block_str) const
    {
        unit_type result;
        std::istringstream(block_str) >> result;

        return result;
    }

    std::string to_string() const
    {

        std::ostringstream oss;
        oss << std::setfill('0');

        if (blocks.size() == 0)
        {
            oss << '0';
        }
        else
        {

            if (!positive)
                oss << '-';
            bool first = true;
            for (auto b_it = blocks.rbegin(); b_it != blocks.rend(); ++b_it)
            {
                if (!first)
                {
                    oss << std::setw(unit_size) << *b_it;
                }
                else
                {
                    oss << *b_it;
                    first = false;
                }
            }
        }

        return oss.str();
    }

    BigInteger operator*(const BigInteger &other) const
    {
        vector<unit_type> result;
        result.resize(this->blocks.size() + other.blocks.size(), 0);

        for (int i = 0; i < this->blocks.size(); ++i)
        {
            for (int j = 0; j < other.blocks.size(); ++j)
            {
                unit_type block = this->blocks[i] * other.blocks[j];

                result[i + j] += block;
            }
        }

        for (int i = 0; i < result.size() - 1; ++i)
        {
            result[i + 1] += result[i] / unit_size_val;
            result[i] = result[i] % unit_size_val;
        }

        auto r_last = result.end();
        r_last--;
        while (*r_last == 0)
            r_last--;
        r_last++;

        BigInteger r(result.begin(), r_last, !(this->positive ^ other.positive));

        return r;
    }

    BigInteger foo(const BigInteger &other) const
    {
        vector<unit_type> result;
        result.resize(this->blocks.size() + other.blocks.size(), 0);

        for (int i = 0; i < this->blocks.size(); ++i)
        {
            for (int j = 0; j < other.blocks.size(); ++j)
            {
                unit_type block = this->blocks[i] * other.blocks[j];
                unit_type block1 = block % unit_size_val;
                unit_type block2 = block / unit_size_val;
                unit_type block3 = 0;

                if (block1 > 0)
                {
                    result[i + j] = result[i + j] + block1;
                    block2 += result[i + j] / unit_size_val;
                    result[i + j] = result[i + j] % unit_size_val;
                }

                if (block2 > 0)
                {
                    result[i + j + 1] = result[i + j + 1] + block2;
                    block3 += result[i + j + 1] / unit_size_val;
                    result[i + j + 1] = result[i + j + 1] % unit_size_val;
                }

                if (block3 > 0)
                {
                    result[i + j + 2] = result[i + j + 2] + block3;
                    block3 += result[i + j + 2] / unit_size_val;
                    result[i + j + 2] = result[i + j + 2] % unit_size_val;
                }
            }
        }

        BigInteger r(result.begin(), result.end(), !(this->positive ^ other.positive));

        return r;
    }
};

int main(int argc, char **argv)
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    std::string val_str1, val_str2;
    std::cin >> val_str1 >> val_str2;

    //std::ostringstream oss;
    //for (int i = 0; i < 300000; ++i)
    //    oss << '9';
    //val_str1 = oss.str();
    //val_str2 = oss.str();

    BigInteger val1(val_str1);
    BigInteger val2(val_str2);

    std::cout << (val1 * val2).to_string() << std::endl;

    return 0;
}
