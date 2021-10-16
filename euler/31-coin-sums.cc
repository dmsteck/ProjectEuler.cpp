//
// Created by daniel on 16/10/2021.
//

#include <catch2/catch.hpp>

#include <array>
#include <iostream>
#include <unordered_set>

namespace {

constexpr unsigned coins[] = {1, 2, 5, 10, 20, 50, 100, 200};

using Combination = std::array<size_t, std::size(coins)>;

struct Hash {
    size_t operator()(const Combination& c) const {
        std::hash<size_t> hasher;
        size_t seed = 0;
        for (const size_t& i : c) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

using Combinations = std::unordered_set<Combination, Hash>;

size_t coin_sums(unsigned target) {
    // combinations[i] is the set of combinations that make up amount "i"
    std::vector<Combinations> combinations(target + 1);

    // the empty set is the unique way to make "0"
    combinations[0].insert(Combination{});

    for (unsigned amount = 1; amount <= target; ++amount) {
        auto& combinations_for_amount = combinations[amount];

        for (size_t i_coin = 0; i_coin < std::size(coins) && coins[i_coin] <= amount; ++i_coin) {
            const unsigned& coin = coins[i_coin];
            for (Combination combination : combinations[amount - coin]) {
                ++combination[i_coin];
                combinations_for_amount.insert(combination);
            }
        }
    }

    return combinations[target].size();
}

} // namespace

TEST_CASE("..31: Coin sums") {

    //std::cout << "31: coin_sums(200): " << coin_sums(200) << std::endl;

    CHECK(coin_sums(0) == 1);
    CHECK(coin_sums(1) == 1);
    CHECK(coin_sums(2) == 2);
    CHECK(coin_sums(3) == 2);
    CHECK(coin_sums(4) == 3);
    CHECK(coin_sums(5) == 4);
    CHECK(coin_sums(200) == 73'682);
}
