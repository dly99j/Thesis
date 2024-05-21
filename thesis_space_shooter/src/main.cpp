#include "../incl/game.hpp"


#ifdef __clang__
const char* comp = "Clang";
#elif defined(__GNUG__)
const char *comp = "GCC";
#else
const char* comp = "Unknown";
#endif

int main() {
    std::cout << "#define __cplusplus: " << __cplusplus << std::endl;
    std::cout << comp << std::endl;
    spsh::game gme;
    gme.run();
}
