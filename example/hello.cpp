#include <reflect/macros>

struct hello_t {
    int i_var = 256;
    void say_hello() {
        std::cout << "hello world from reflected function" << std::endl;
    }

    int multiply_by_two(int x) {
        return x * 2;
    }
};

rtti_type(hello_t);
rtti_type(std, string);
rtti_method(hello_t, say_hello, void);
rtti_method(hello_t, multiply_by_two, int, int);
rtti_field(hello_t, int, i_var);
