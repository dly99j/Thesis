//
// Created by htamas on 2023.11.09..
//

#ifndef TRANSFORMS_UTILS_HPP
#define TRANSFORMS_UTILS_HPP

#include <type_traits>
#include <concepts>

template<std::size_t M, std::size_t N>
struct is_same_size_t : std::false_type {};

template<std::size_t M>
struct is_same_size_t<M, M> : std::true_type {};

template<std::size_t M, std::size_t N>
inline constexpr bool is_same_size_t_v = is_same_size_t<M, N>::value;

template<class T>
concept number =  std::is_floating_point_v<T> || std::is_integral_v<T>;

#endif //TRANSFORMS_UTILS_HPP
