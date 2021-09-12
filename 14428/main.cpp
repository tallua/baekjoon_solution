#include <bit>
#include <iostream>
#include <limits>
#include <vector>

template<typename _T, typename _Cmp = std::less<_T>>
struct Segtree
{
public:
    struct range_t
    {
        std::size_t index;
        std::size_t left;
        std::size_t right;

        std::size_t mid() const { return (left + right) / 2; }
        std::size_t left_index() const { return left_index(index); }
        std::size_t right_index() const { return right_index(index); }
        static std::size_t left_index(std::size_t i) { return i * 2 + 1; }
        static std::size_t right_index(std::size_t i) { return i * 2 + 2; }

        range_t left_range() const { return { left_index(), left, mid() }; }
        range_t right_range() const { return { right_index(), mid(), right }; }

        bool is_unique() const { return right <= left + 1; }
        bool in(std::size_t l, std::size_t r) const { return l <= left && right <= r; }
        bool overlaps(std::size_t l, std::size_t r) const { return !(right <= l) && !(r <= left); }
    };

public:
    template<typename _Iter>
    Segtree(std::size_t N, _Iter begin, _T default_val = _T(), _Cmp reducer = _Cmp())
      : m_size(std::bit_ceil(N))
      , m_cmp(reducer)
      , m_default_val(default_val)
      , m_data(m_size * 2 - 1)
    {
        m_data[m_size - 1] = *begin;
        for (std::size_t i = 1; i < N; ++i) {
            ++begin;
            m_data[m_size + i - 1] = *begin;
        }

        std::size_t index = m_size >> 1;
        while (index != 0) {
            for (std::size_t i = 0; i < index; ++i) {
                auto const& lhs = m_data[range_t::left_index(index + i - 1)];
                auto const& rhs = m_data[range_t::right_index(index + i - 1)];
                m_data[index + i - 1] = m_cmp(lhs, rhs) ? lhs : rhs;
            }
            index = index >> 1;
        }
    }

    // Segtree(std::vector<_T> data, _T default_val = _T(), _Cmp reducer = _Cmp())
    //    : Segtree(data.size(), data.begin(), default_val, reducer)
    //{
    //}

    void update(std::size_t index, _T data);
    _T query(std::size_t begin, std::size_t end) const;

public:
    _T query(std::size_t begin, std::size_t end, range_t range) const;

private:
    const std::size_t m_size;
    const _Cmp m_cmp;
    const _T m_default_val;
    std::vector<_T> m_data;
};

template<typename _T, typename _Cmp>
void
Segtree<_T, _Cmp>::update(std::size_t index, _T data)
{
    index += m_size - 1;
    m_data[index] = std::move(data);
    while (index != 0) {
        index = (index - 1) / 2;
        auto const& lhs = m_data[range_t::left_index(index)];
        auto const& rhs = m_data[range_t::right_index(index)];
        m_data[index] = m_cmp(lhs, rhs) ? lhs : rhs;
    }
}

template<typename _T, typename _Cmp>
_T
Segtree<_T, _Cmp>::query(std::size_t begin, std::size_t end) const
{
    return query(begin, end, { 0, 0, m_size });
}

template<typename _T, typename _Cmp>
_T
Segtree<_T, _Cmp>::query(std::size_t begin, std::size_t end, range_t range) const
{
    if (!range.overlaps(begin, end)) {
        return m_default_val;
    }

    if (range.in(begin, end)) {
        return m_data[range.index];
    }

    auto const& lhs = query(begin, end, range.left_range());
    auto const& rhs = query(begin, end, range.right_range());
    return m_cmp(lhs, rhs) ? lhs : rhs;
}

struct Data
{
    int value = std::numeric_limits<int>::max();
    int index = std::numeric_limits<int>::max();
};

inline bool
operator<(Data const& lhs, Data const& rhs)
{
    return lhs.value != rhs.value ? lhs.value < rhs.value : lhs.index < rhs.index;
};

struct DataReader
{
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Data;
    using pointer = Data*;   // or also value_type*
    using reference = Data&; // or also value_type&

public:
    DataReader(std::istream& is)
      : m_is(std::addressof(is))
      , m_data({ 0, 0 })
    {
        read();
    }

    DataReader(const DataReader& other)
      : m_is(other.m_is)
      , m_data(other.m_data)
    {}

    reference operator*() { return m_data; }
    pointer operator->() { return &m_data; }

    DataReader& operator++()
    {
        read();
        return *this;
    }
    DataReader operator++(int)
    {
        DataReader tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(DataReader const& lhs, DataReader const& rhs) noexcept { return lhs.m_is == rhs.m_is; }
    friend bool operator!=(DataReader const& lhs, DataReader const& rhs) noexcept { return !(lhs == rhs); }

private:
    void read()
    {
        m_data.index++;
        (*m_is) >> m_data.value;
    }

private:
    std::istream* m_is;
    Data m_data;
};

int
main(int argc, char** argv)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t N;
    std::cin >> N;

    Segtree<Data> segtree(N, DataReader(std::cin));

    std::size_t M;
    std::cin >> M;
    while (M--) {
        int op, i, j;
        std::cin >> op >> i >> j;

        switch (op) {
            case 1: {
                segtree.update(i - 1, { j, i });
                break;
            }
            case 2: {
                std::cout << segtree.query(i - 1, j).index << '\n';
                break;
            }
        }
    }

    return 0;
}