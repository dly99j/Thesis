//
// Created by htamas on 2023.11.08..
//

#ifndef TRANSFORMS_GENERIC_VECTOR_HPP
#define TRANSFORMS_GENERIC_VECTOR_HPP

#include <cstddef>
#include <array>
#include <cmath>
#include <ranges>
#include <concepts>
#include "utils.hpp"

template<number Type, std::size_t Size>
class generic_vector {

public:
    explicit generic_vector(Type value = 0)                            { init_array(value); }
    explicit generic_vector(const std::array<Type, Size> &t_points)    : m_points(t_points) {}
    explicit generic_vector(const std::array<Type, Size> &&t_points)   : m_points(std::move(t_points)) {}

public:
    generic_vector<Type, Size> operator+(const generic_vector<Type, Size> &);
    generic_vector<Type, Size> operator-(const generic_vector<Type, Size> &);

public:
    std::size_t                     dimension() { return Size; }
    Type                            length();
    Type                            distance_from(generic_vector<Type, Size> &);
    Type                            scalar_product(generic_vector<Type, Size> &);
    const std::array<double, Size>  get_points() const { return m_points; };

private:
    constexpr void init_array(Type = 0);

protected:
    std::array<Type, Size> m_points;
};

/*
 * specified cases for 2- and 3-dimensional vectors
 * because those are the ones that will be used the most
 * thus they have to be the most optimal implementations
 *
 * edit: I was wrong, 4-dimensional ones will be the most prominent
 * fuck me then
 *
 * why am i making a generic vector anyways... I'm only going to use
 * one specific template instantiation
 */

//TODO possible constexpring, const correctness check?

template<number Type, std::size_t Size>
generic_vector<Type, Size> generic_vector<Type, Size>::operator+(const generic_vector<Type, Size> &other) {
    if constexpr (Size == 2) {
        return generic_vector<Type, Size>
                (std::array{m_points[0] + other.m_points[0],
                            m_points[1] + other.m_points[1]});
    } else if constexpr (Size == 3) {
        return generic_vector<Type, Size>
                (std::array{m_points[0] + other.m_points[0],
                            m_points[1] + other.m_points[1],
                            m_points[2] + other.m_points[2]});
    } else {
        std::array<Type, Size> new_points;
        for (std::size_t i = 0; i < Size; ++i) {
            new_points[i] = m_points[i] + other.m_points[i];
        }
        return generic_vector<Type, Size>{new_points};
    }
}

template<number Type, std::size_t Size>
generic_vector<Type, Size> generic_vector<Type, Size>::operator-(const generic_vector<Type, Size> &other) {
    if constexpr (Size == 2) {
        return generic_vector<Type, Size>
                (std::array{m_points[0] - other.m_points[0],
                            m_points[1] - other.m_points[1]});
    } else if constexpr (Size == 3) {
        return generic_vector<Type, Size>
                (std::array{m_points[0] - other.m_points[0],
                            m_points[1] - other.m_points[1],
                            m_points[2] - other.m_points[2]});
    } else {
        std::array<Type, Size> new_points;
        for (std::size_t i = 0; i < Size; ++i) {
            new_points[i] = m_points[i] - other.m_points[i];
        }
        return generic_vector<Type, Size>{new_points};
    }
}

template<number Type, std::size_t Size>
Type generic_vector<Type, Size>::length() {
    if constexpr (Size == 2) {
        return std::hypot(m_points[0], m_points[1]);
    } else if constexpr (Size == 3) {
        return std::hypot(m_points[0], m_points[1], m_points[2]);
    } else {
        Type to_sqrt = 0;
        for (const auto i: m_points) {
            to_sqrt += std::pow(i, 2);
        }
        return std::sqrt(to_sqrt);
    }
}


template<number Type, std::size_t Size>
Type generic_vector<Type, Size>::distance_from(generic_vector<Type, Size> &other) {
    if constexpr (Size == 2) {
        return std::hypot(m_points[0] - other.m_points[0],
                          m_points[1] - other.m_points[1]);
    } else if constexpr (Size == 3) {
        return std::hypot(m_points[0] - other.m_points[0],
                          m_points[1] - other.m_points[1],
                          m_points[2] - other.m_points[2]);
    } else {
        Type to_sqrt = 0;
        for (std::size_t i = 0; i < Size; ++i) {
            to_sqrt += std::pow(m_points[i] - other.m_points[i], 2);
        }
        return std::sqrt(to_sqrt);
    }
}


template<number Type, std::size_t Size>
Type generic_vector<Type, Size>::scalar_product(generic_vector<Type, Size> &other) {
    if constexpr (Size == 2) {
        return m_points[0] * other.m_points[0]
               + m_points[1] * other.m_points[1];
    } else if constexpr (Size == 3) {
        return m_points[0] * other.m_points[0]
               + m_points[1] * other.m_points[1]
               + m_points[2] * other.m_points[2];
    } else {
        Type to_ret = 0;
        for (std::size_t i = 0; i < Size; ++i) {
            to_ret += m_points[i] * other.m_points[i];
        }
        return to_ret;
    }
}

template<number Type, std::size_t Size>
constexpr void generic_vector<Type, Size>::init_array(Type value) {
    for (auto& i : m_points) {
        i = value;
    }
}


#endif //TRANSFORMS_GENERIC_VECTOR_HPP
