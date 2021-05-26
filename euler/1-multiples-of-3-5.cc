#include <catch2/catch.hpp>

#include <iostream>
#include <limits>

namespace {

// Let's make sure the result fits into unsigned.
// 500'000 = 1'000 * 1'001 / 2 is an upper bound for the result.
static_assert(std::numeric_limits<unsigned>::max() >= 500'500);

unsigned naive_sum_of_multiples_of_3_and_5(unsigned n) {
    unsigned current = 0;
    unsigned result = 0;

    // Branch-free loop. I'm sure there's a more efficient implementation that
    // computes the sum up to the nearest multiple of 15 directly.
    while (current < n) {
        result += current;
        const unsigned next_multiple_of_3 = (current / 3 + 1) * 3;
        const unsigned next_multiple_of_5 = (current / 5 + 1) * 5;
        current = std::min(next_multiple_of_3, next_multiple_of_5);
    }

    return result;
}

unsigned fast_sum_of_multiples_of_3_and_5(unsigned n) {

    // Represent n = 15 * n_over_15 + remainder
    const unsigned n_over_15 = n / 15;
    const unsigned remainder = n % 15;

    // Sum of multiples of 3 and 5 up to (excluding) 15 * n_over_15
    unsigned result = ((105 * n_over_15 - 15) * n_over_15) / 2;

    const unsigned multiples_between_0_and_15[] = {0, 3, 5, 6, 9, 10, 12};

    for (const unsigned i : multiples_between_0_and_15) {
        if (i < remainder) {
            result += 15 * n_over_15 + i;
        }
    }

    return result;
}

} // namespace

TEST_CASE("1: Multiples of 3 and 5") {
    CHECK(naive_sum_of_multiples_of_3_and_5(10) == 23);
    CHECK(fast_sum_of_multiples_of_3_and_5(10) == 23);
    CHECK(naive_sum_of_multiples_of_3_and_5(1000) == fast_sum_of_multiples_of_3_and_5(1000));

    std::cout << "1: sum_of_multiples_of_3_and_5(1000): " << naive_sum_of_multiples_of_3_and_5(1000) << std::endl;
}
