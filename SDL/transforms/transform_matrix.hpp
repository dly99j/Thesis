//
// Created by htamas on 2023.11.09..
//

#ifndef TRANSFORMS_TRANSFORM_MATRIX_HPP
#define TRANSFORMS_TRANSFORM_MATRIX_HPP

#include "utils.hpp"
#include "generic_matrix.hpp"

template<number Type>
class transform_matrix : public generic_matrix<Type, 4, 4> {
    using generic_matrix<Type, 4, 4>::generic_matrix;
};



#endif //TRANSFORMS_TRANSFORM_MATRIX_HPP
