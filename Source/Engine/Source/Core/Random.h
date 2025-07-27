#pragma once
#include <cstdlib>
#include <random>
#include <type_traits>

namespace viper::random {

    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    template <typename T = float, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    inline T getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    template <typename T = float, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    inline T getReal(T max) {
        return getReal<T>(static_cast<T>(0), max);
    }

    template <typename T = float, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }
}
