//
// Created by daniel on 16/10/2021.
//

#include <catch2/catch.hpp>

#include <iostream>

namespace {

struct PrimeFinder {
    std::vector<unsigned> primes = {2, 3, 5, 7};

    void find_prime() {
        for (unsigned candidate = primes.back() + 2;; candidate += 2) {
            bool candidate_is_prime = true;

            for (size_t ip = 0; ip < primes.size() //
                 && primes[ip] * primes[ip] <= candidate //
                 && candidate_is_prime;
                 ++ip) {
                candidate_is_prime &= (candidate % primes[ip] != 0);
            }

            if (candidate_is_prime) {
                primes.push_back(candidate);
                break;
            }
        }
    }
};

unsigned nth_prime(unsigned n) {
    assert(n > 0);

    PrimeFinder prime_finder{};

    while (prime_finder.primes.size() < n) {
        prime_finder.find_prime();
    }

    return prime_finder.primes[n - 1];
}

} // namespace

TEST_CASE("...7: 10'001st prime") {

    //std::cout << "7: nth_prime(10'001): " << nth_prime(10'001) << std::endl;

    CHECK(nth_prime(1) == 2);
    CHECK(nth_prime(2) == 3);
    CHECK(nth_prime(3) == 5);
    CHECK(nth_prime(4) == 7);
    CHECK(nth_prime(5) == 11);
    CHECK(nth_prime(6) == 13);
    CHECK(nth_prime(7) == 17);
    CHECK(nth_prime(8) == 19);
    CHECK(nth_prime(9) == 23);
    CHECK(nth_prime(10) == 29);
    CHECK(nth_prime(10'001) == 104'743);
}
