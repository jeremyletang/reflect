reflect
=======

C++ reflection framework (for fun)

simple example:

```cpp
#include <reflect/class.h>
#include <reflect/object.h>
#include <reflect/method.h>

int
main() {
    rf::class_t clss = rf::class_t::for_name("hello_t");
    rf::object_t object = clss.new_instance();
    rf::method_t method = clss.get_method("say_hello");
    method.invoke(object);
}

```