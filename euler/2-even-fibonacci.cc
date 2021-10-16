#include <catch2/catch.hpp>

#include <iostream>
#include <limits>

namespace {

struct FibonacciSequence {
    // Start with k = 0
    unsigned f_k = 0;
    unsigned f_k_plus_1 = 1;

    unsigned operator()() {
        const unsigned result = f_k;
        f_k = f_k_plus_1;
        f_k_plus_1 += result;
        return result;
    }
};

unsigned sum_of_even_fibonacci(unsigned max) {
    FibonacciSequence fibonacci{};
    unsigned result = 0;

    for (unsigned current = fibonacci(); current <= max; current = fibonacci()) {
        if (current % 2 == 0) {
            result += current;
        }
    }

    return result;
}

// TODO
// Fibonacci sequence F_0 = 0, 1, 1, 2, 3, 5 ...
// Every third Fibonacci number is even.
// Recall that F_k = 1/sqrt(5) * ( phi^n - psi^n ),
// where phi = (1 + sqrt(5))/2 is the golden ratio and psi = phi - 1.
// Hence, summing all even Fibonacci numbers is a simple geometric sum.

} // namespace

TEST_CASE("...2: Even Fibonacci numbers") {

    //std::cout << "2: sum_of_even_fibonacci(4'000'000): " << sum_of_even_fibonacci(4'000'000) << std::endl;

    CHECK(sum_of_even_fibonacci(1) == 0);
    CHECK(sum_of_even_fibonacci(2) == 2);
    CHECK(sum_of_even_fibonacci(10) == 10);
    CHECK(sum_of_even_fibonacci(4'000'000) == 4'613'732);
}
