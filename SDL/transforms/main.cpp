#include <SDL2/SDL.h>
#include "generic_vector.hpp"
#include <iostream>

#include "generic_matrix.hpp"
#include "transform_matrix.hpp"


int main() {
    std::array<std::array<double, 4>, 4> arr;
    transform_matrix<double> m1(std::move(arr));
}
