// http://boj.kr/5dfc423786044f2e8334899645e7e3d3

#include <iostream>
#include <bit>
#include <string>
#include <vector>
#include <numbers>
#include <algorithm>
#include <complex>
#include <sstream>

using namespace std;
using complex_seq = std::vector<std::complex<double>>;
const auto pi = std::numbers::pi;

std::string to_string(complex_seq const& seq)
{
    std::ostringstream oss;

    int carry = 0;
    std::for_each(seq.begin(), seq.end(), [&](std::complex<double> const num) {
        carry += std::round(num.real());
        oss << (carry % 10);
        carry /= 10;
    });

    std::string result = oss.str();
    while (result.size() > 0 && result.back() == '0') {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());

    if (result.size() == 0) {
        return "0";
    }

    return result;
}

std::ostream& operator << (std::ostream& os, complex_seq const& seq)
{
    std::for_each(seq.begin(), seq.end(), [&](std::complex<double> const num) {
        os << "(" << num.real() << ", " << num.imag() << ")";
    });

    return os;
}

complex_seq to_seq(std::string const& str, std::size_t const size)
{
    complex_seq seq(size);

    std::transform(str.rbegin(), str.rend(), seq.begin(), [](char ch) {
        return std::complex<double>(ch - '0', 0);
    });

    return seq;
}

void fourier_transform(complex_seq& seq, std::complex<double> const w)
{
    if (seq.size() == 1) {
        return;
    }

    const auto half_size = seq.size() / 2;
    complex_seq even(half_size);
    complex_seq odd(half_size);

    for (auto i = 0; i < seq.size(); ++i)
    {
        (i % 2 ? odd : even)[i / 2] = seq[i];
    }

    fourier_transform(even, w * w);
    fourier_transform(odd, w * w);

    std::complex<double> wp(1, 0);
    for (int i = 0; i < half_size; ++i) {
        seq[i] = even[i] + wp * odd[i];
        seq[i + half_size] = even[i] - wp * odd[i];
        wp *= w;
    }
}


std::string multiply(std::string const& n1_str, std::string const& n2_str)
{
    const auto size = std::max(std::bit_ceil(n1_str.size()),
                               std::bit_ceil(n2_str.size())) * 2;

    auto n1 = to_seq(n1_str, size);
    auto n2 = to_seq(n2_str, size);

    const auto w = std::complex<double>(cos(pi * 2 / size), sin(pi * 2 / size));

    fourier_transform(n1, w);
    fourier_transform(n2, w);

    complex_seq mult(size);
    for (auto i = 0; i < size; ++i) {
        mult[i] = n1[i] * n2[i];
    }

    fourier_transform(mult, std::complex<double>(1, 0) / w);
    std::transform(mult.begin(), mult.end(), mult.begin(), [size](auto const& num) { 
        return num / std::complex<double>(size, 0);
    });

    return to_string(mult);
}

int main(int argc, char** argv)
{
    std::string n1, n2;
    std::cin >> n1 >> n2;

    const auto mult = multiply(n1, n2);

    std::cout << mult << '\n';

    return 0;
}