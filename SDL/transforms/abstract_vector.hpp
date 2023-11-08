//
// Created by htamas on 2023.11.08..
//

#ifndef TRANSFORMS_ABSTRACT_VECTOR_HPP
#define TRANSFORMS_ABSTRACT_VECTOR_HPP

#include <cstddef>
#include <array>
#include <cmath>
#include <ranges>
#include <concepts>

template<class T>
concept floating_point_or_integral =  std::is_floating_point_v<T> || std::is_integral_v<T>;

template<floating_point_or_integral Type, std::size_t Size>
class abstract_vector {

public:
    abstract_vector()                                                   : m_points({}) {}
    explicit abstract_vector(const std::array<Type, Size> &t_points)    : m_points(t_points) {}
    explicit abstract_vector(const std::array<Type, Size> &&t_points)   : m_points(std::move(t_points)) {}

public:
    abstract_vector<Type, Size> operator+(const abstract_vector<Type, Size> &other);
    abstract_vector<Type, Size> operator-(const abstract_vector<Type, Size> &other);

public:
    std::size_t                     dimension() { return Size; }
    Type                            length();
    Type                            distance_from(abstract_vector<Type, Size> &other);
    Type                            scalar_product(abstract_vector<Type, Size> &other);
    const std::array<double, Size>  get_points() const { return m_points; };

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
 */

template<floating_point_or_integral Type, std::size_t Size>
abstract_vector<Type, Size> abstract_vector<Type, Size>::operator+(const abstract_vector<Type, Size> &other) {
    if constexpr (Size == 2) {
        return abstract_vector<Type, Size>
                (std::array{m_points[0] + other.m_points[0],
                            m_points[1] + other.m_points[1]});
    } else if constexpr (Size == 3) {
        return abstract_vector<Type, Size>
                (std::array{m_points[0] + other.m_points[0],
                            m_points[1] + other.m_points[1],
                            m_points[2] + other.m_points[2]});
    } else {
        std::array<Type, Size> new_points;
        for (std::size_t i = 0; i < Size; ++i) {
            new_points[i] = m_points[i] + other.m_points[i];
        }
        return abstract_vector<Type, Size>{new_points};
    }
}

template<floating_point_or_integral Type, std::size_t Size>
abstract_vector<Type, Size> abstract_vector<Type, Size>::operator-(const abstract_vector<Type, Size> &other) {
    if constexpr (Size == 2) {
        return abstract_vector<Type, Size>
                (std::array{m_points[0] - other.m_points[0],
                            m_points[1] - other.m_points[1]});
    } else if constexpr (Size == 3) {
        return abstract_vector<Type, Size>
                (std::array{m_points[0] - other.m_points[0],
                            m_points[1] - other.m_points[1],
                            m_points[2] - other.m_points[2]});
    } else {
        std::array<Type, Size> new_points;
        for (std::size_t i = 0; i < Size; ++i) {
            new_points[i] = m_points[i] - other.m_points[i];
        }
        return abstract_vector<Type, Size>{new_points};
    }
}

template<floating_point_or_integral Type, std::size_t Size>
Type abstract_vector<Type, Size>::length() {
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


template<floating_point_or_integral Type, std::size_t Size>
Type abstract_vector<Type, Size>::distance_from(abstract_vector<Type, Size> &other) {
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


template<floating_point_or_integral Type, std::size_t Size>
Type abstract_vector<Type, Size>::scalar_product(abstract_vector<Type, Size> &other) {
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

#endif //TRANSFORMS_ABSTRACT_VECTOR_HPP
