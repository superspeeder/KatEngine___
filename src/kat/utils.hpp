#pragma once

#include <type_traits>
#include <concepts>
#include <unordered_set>


namespace kat {
    template<typename T>
    concept numeric = std::is_arithmetic_v<T>;
}