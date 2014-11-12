#include <iostream>

#include "reflect/class.h"
#include "reflect/object.h"
#include "reflect/method.h"

int
main() {
    rf::class_t klass = rf::class_t::for_name("hello_t");
    rf::object_t object = klass.new_instance();
    if (klass == nullptr) { std::cout << "klass null" << std::endl; }
    if (object == nullptr) { std::cout << "object null" << std::endl; }
    rf::method_t method = klass.get_method("say_hello");
    if (object == nullptr) { std::cout << "method null" << std::endl; }
    else { method.invoke(object); }
}
