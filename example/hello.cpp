#include "reflect/macros.h"

struct hello_t {
    int i_var = 0;
    void say_hello() {
        std::cout << "hello world from reflected function" << std::endl;
    }
};

rtti_type(hello_t);
rtti_type(std, string);
rtti_method(hello_t, say_hello, void);
rtti_field(hello_t, int, i_var);
