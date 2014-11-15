#include <iostream>

#include <reflect/class.h>
#include <reflect/object.h>
#include <reflect/method.h>

int
main() {
    rf::class_t klass = rf::class_t::for_name("hello_t");
    rf::object_t object = klass.new_instance();
    if (klass == nullptr) { std::cout << "klass null" << std::endl; }
    if (object == nullptr) { std::cout << "object null" << std::endl; }
    rf::method_t method1 = klass.get_method("say_hello");
    if (method1 == nullptr) { std::cout << "say_hello don't exist" << std::endl; }
    else { method1.invoke(object); }
    std::cout << method1.to_string() << std::endl;
    rf::method_t method2 = klass.get_method("multiply_by_two");
    if (method2 == nullptr) { std::cout << "multiply_by_two don't exist" << std::endl; }
    else { std::cout << method2.invoke<int>(object, 42) << std::endl; }
    std::cout << method2.to_string() << std::endl;
}
