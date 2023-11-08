#include <SDL2/SDL.h>
#include "abstract_vector.hpp"
#include <iostream>

int main() {
    abstract_vector<double, 3> vec{{7, 4, 4}};
    abstract_vector<double, 4> vec2{{17, 6, 2, 4}};
    //auto vec3 = vec + vec2;
    std::cout << vec.get_points()[0];
}
