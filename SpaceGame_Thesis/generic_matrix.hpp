//
// Created by htamas on 2023.12.15..
//

#ifndef GENERIC_MATRIX_HPP
#define GENERIC_MATRIX_HPP

//#include <concepts>
#include <array>
#include "utils.hpp"

template<number Type, std::size_t M, std::size_t N>
class generic_matrix {

public:
    explicit generic_matrix(Type t_value = 0)                               { init_array(t_value); }
    explicit generic_matrix(std::array<std::array<Type, N>, M> &t_matrix)   : m_matrix(t_matrix) {}
    explicit generic_matrix(std::array<std::array<Type, N>, M> &&t_matrix)  : m_matrix(std::move(t_matrix)) {}

public:
    generic_matrix<Type, M, N> operator+(const generic_matrix<Type, M, N> &);
    generic_matrix<Type, M, N> operator-(const generic_matrix<Type, M, N> &);
    template<number OtherType, std::size_t OtherM, std::size_t OtherN,
            std::enable_if_t<std::is_same_v<Type, OtherType>, bool> = true,
            std::enable_if_t<is_same_size_t_v<N, OtherM>, bool> = true>
    generic_matrix<Type, M, OtherN> operator*(const generic_matrix<OtherType, OtherM, OtherN> &);
    std::array<Type, N>& operator[](std::size_t);
    const std::array<Type, N>& operator[](std::size_t) const;

private:
    constexpr void init_array(Type = 0);

protected:
    std::array<std::array<Type, N>, M> m_matrix;
};


template<number Type, std::size_t M, std::size_t N>
generic_matrix<Type, M, N> generic_matrix<Type, M, N>::operator+(const generic_matrix<Type, M, N> &other) {
    generic_matrix<Type, M, N> to_ret;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            to_ret[i][j] = m_matrix[i][j] + other[i][j];
        }
    }
    return to_ret;
}


template<number Type, std::size_t M, std::size_t N>
generic_matrix<Type, M, N> generic_matrix<Type, M, N>::operator-(const generic_matrix<Type, M, N> &other) {
    generic_matrix<Type, M, N> to_ret;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            to_ret[i][j] = m_matrix[i][j] - other[i][j];
        }
    }
    return to_ret;
}


template<number Type, std::size_t M, std::size_t N>
template<number OtherType, std::size_t OtherM, std::size_t OtherN,
        std::enable_if_t<std::is_same_v<Type, OtherType>, bool>,
        std::enable_if_t<is_same_size_t_v<N, OtherM>, bool>>
generic_matrix<Type, M, OtherN> generic_matrix<Type, M, N>::operator*(const generic_matrix<OtherType, OtherM, OtherN> &other) {
    generic_matrix<Type, M, OtherN> to_ret;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < OtherN; ++j) {
            Type sum = 0;
            for (std::size_t k = 0; k < M; ++k) {
                sum += m_matrix[i][k] * other[k][j];
            }
            to_ret[i][j] = sum;
        }
    }
    return to_ret;
}


template<number Type, std::size_t M, std::size_t N>
std::array<Type, N> &generic_matrix<Type, M, N>::operator[](std::size_t index) {
    return m_matrix[index];
}


template<number Type, std::size_t M, std::size_t N>
const std::array<Type, N> &generic_matrix<Type, M, N>::operator[](std::size_t index) const {
    return m_matrix[index];
}


template<number Type, std::size_t M, std::size_t N>
constexpr void generic_matrix<Type, M, N>::init_array(Type value) {
    for (auto& i : m_matrix) {
        for (auto& j : i) {
            j = value;
        }
    }
}


#endif //GENERIC_MATRIX_HPP
