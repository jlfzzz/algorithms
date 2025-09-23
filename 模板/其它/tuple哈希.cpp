#include "bits/stdc++.h"
using namespace std;

template <typename T>
inline void hash_combine(size_t &seed, const T &val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct TupleHashImpl {
    static void apply(size_t &seed, const Tuple &t) {
        TupleHashImpl<Tuple, Index - 1>::apply(seed, t);
        hash_combine(seed, std::get<Index>(t));
    }
};

template <typename Tuple>
struct TupleHashImpl<Tuple, 0> {
    static void apply(size_t &seed, const Tuple &t) {
        hash_combine(seed, std::get<0>(t));
    }
};

namespace std {
    template <typename... Args>
    struct hash<std::tuple<Args...>> {
        size_t operator()(const std::tuple<Args...> &t) const {
            size_t seed = 0;
            TupleHashImpl<std::tuple<Args...>>::apply(seed, t);
            return seed;
        }
    };
}