//#include <memory>

struct S {
    int x;
    double y;

    struct {
        long z;
    };
};

int main() {
    //std::unique_ptr<int> i = std::make_unique<int>(1);
    S ss;
    ss.x = 1;
    ss.z = ss.x;
    ss.y = ss.x + ss.z;
}