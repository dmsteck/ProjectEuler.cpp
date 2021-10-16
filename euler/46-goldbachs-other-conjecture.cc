//
// Created by daniel on 16/10/2021.
//

#include <catch2/catch.hpp>

#include <iostream>

namespace {

struct PrimeFinder {
    std::vector<unsigned> primes = {2};

    // Must be called in strictly monotonic order that visits all odd primes.
    bool is_prime(unsigned value) {
        if (value <= 2) {
            return (value == 2);
        }

        assert(value > primes.back());

        bool value_is_prime = true;

        for (size_t ip = 0; ip < primes.size() //
             && primes[ip] * primes[ip] <= value //
             && value_is_prime;
             ++ip) {
            value_is_prime &= (value % primes[ip] != 0);
        }

        if (value_is_prime) {
            primes.push_back(value);
        }

        return value_is_prime;
    }
};

bool is_square(unsigned value) {
    const double sqrt_value = std::sqrt(value);
    const unsigned maybe_sqrt = static_cast<unsigned>(sqrt_value + 0.1);
    return (maybe_sqrt * maybe_sqrt == value);
}

struct GoldbachConjecture {
    unsigned n = 1;

    PrimeFinder prime_finder;

    // Process `n + 2` and return true if it doesn't violate Goldbach's other conjecture;
    // i.e., if `n + 2` is a prime OR an even composite OR an odd composite that can be
    // represented as the sum of a prime and twice a square.
    bool process_number() {
        n += 2;

        const bool n_is_prime = prime_finder.is_prime(n);

        if (n_is_prime) {
            return true;
        }

        assert(n % 2 == 1);

        for (size_t i = 1; i < prime_finder.primes.size(); ++i) {
            const unsigned& p = prime_finder.primes[i];

            assert(p % 2 == 1);
            assert(p < n);

            if (is_square((n - p) / 2)) {
                return true;
            }
        }

        return false;
    }
};

} // namespace

TEST_CASE("..46: Goldbach's other conjecture") {

    GoldbachConjecture goldbach_conjecture{};

    constexpr size_t max_iterations = 10'000;

    bool conjecture = true;

    for (size_t i = 0; i < max_iterations; ++i) {
        conjecture &= goldbach_conjecture.process_number();
        if (!conjecture) {
            break;
        }
    }

    CHECK(!conjecture);

    // std::cout << "46: Smallest number that violates Goldbach's other conjecture: " << goldbach_conjecture.n << std::endl;
}
