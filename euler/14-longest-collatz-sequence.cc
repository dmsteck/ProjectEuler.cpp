//
// Created by daniel on 16/10/2021.
//

#include <catch2/catch.hpp>

#include <iostream>
#include <unordered_map>

namespace {

struct CollatzDistance {
    std::unordered_map<unsigned, unsigned> cache;

    explicit CollatzDistance() : cache{{1, 0}} {}

    // Collatz distance to 1
    unsigned operator()(unsigned value) {
        assert(value > 0);

        const auto cached = cache.find(value);
        if (cached != cache.end()) {
            return cached->second;
        }

        const unsigned next = (value % 2 == 0) ? (value / 2) : (3 * value + 1);
        const unsigned result = 1 + (*this)(next);

        cache[value] = result;
        return result;
    }
};

unsigned longest_collatz_sequence(unsigned max) {
    CollatzDistance collatz_distance;

    unsigned best_number = 1;
    unsigned best_distance = 0;

    for (unsigned i = 1; i <= max; ++i) {
        const size_t dist = collatz_distance(i);
        if (dist > best_distance) {
            best_number = i;
            best_distance = dist;
        }
    }

    return best_number;
}

} // namespace

TEST_CASE("..14: Longest Collatz sequence") {

    //std::cout << "14: longest_collatz_sequence(1'000'000): " << longest_collatz_sequence(1'000'000) << std::endl;

    CHECK(longest_collatz_sequence(1'000'000) == 837'799);
}

