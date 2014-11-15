// The MIT License (MIT)
//
// Copyright (c) 2014 Jeremy Letang
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef REFLECT_CLASS
#define REFLECT_CLASS

#include <cstddef>
#include <string>
#include <dlfcn.h>

#include "object.h"
#include "method.h"
#include "private/dl.h"

namespace rf {

#define name_prefix "_instanciate_reflectable_type_";
#define method_prefix "_method_reflectable_"

class class_t {

private:

    std::string name;
    void *(*constructor)() = nullptr;
    char *error = nullptr;

    class_t()
    : name(""), constructor(nullptr), error(nullptr) {}

public:

    ~class_t() {}

    static class_t for_name(std::string class_name) {
        class_t class_tmp;

        class_tmp.name = class_name;

        // load function constructor
        std::string fn_name = name_prefix;
        fn_name += class_tmp.name;

        class_tmp.constructor = dl::get_instance().get_constructor(fn_name);

        return class_tmp;
    }

    object_t new_instance() {
        void *ptr_instance = nullptr;

        if (this->constructor != nullptr) {
            ptr_instance = (*this->constructor)();
        }

        return object_t(this->name, ptr_instance);
    }

    method_t get_method(std::string method_name) {
        void *(*ptr_method)(void*) = nullptr;

        // load function method
        std::string fn_name = method_prefix;
        fn_name += method_name;
        fn_name += "_";
        fn_name += this->name;
        ptr_method = dl::get_instance().get_method(fn_name);

        return method_t(method_name, this->name, ptr_method);
    }

    friend bool operator==(std::nullptr_t nullp, class_t &c);
    friend bool operator==(class_t &c, std::nullptr_t nullp);
    friend bool operator!=(std::nullptr_t nullp, class_t &c);
    friend bool operator!=(class_t &c, std::nullptr_t nullp);

};

bool
operator==(std::nullptr_t nullp, class_t &c) {
    return c.constructor == nullptr;
}

bool
operator==(class_t &c, std::nullptr_t nullp) {
    return c.constructor == nullptr;
}

bool
operator!=(std::nullptr_t nullp, class_t &c) {
    return c.constructor != nullptr;
}

bool
operator!=(class_t &c, std::nullptr_t nullp) {
    return c.constructor != nullptr;
}

// FIXME: is_instance(Object obj), get_name, to_string

}

#endif
