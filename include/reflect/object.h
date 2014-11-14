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

#ifndef REFLECT_OBJECT
#define REFLECT_OBJECT

#include "class.h"
#include "method.h"
#include "private/dl.h"

namespace rf {

#define method_prefix "_method_reflectable_"

class object_t {

    friend class class_t;

private:

    std::string name;
    void *ptr;

    object_t() = delete;
    object_t(std::string name, void *ptr)
    : name(name), ptr(ptr) {}

public:

    template<typename T> T &get() {
        return *static_cast<T*>(this->ptr);
    }

    void *get_ptr() {
        return this->ptr;
    }

    method_t get_method(std::string method_name) {
        void *(*ptr_method)(void*) = nullptr;

        // load function method
        std::string fn_name = method_prefix;
        fn_name += method_name;
        fn_name += "_";
        fn_name += this->name;
        ptr_method = dl::get_instance().get_method(fn_name);

        return method_t(method_name, ptr_method);
    }

    friend bool operator==(std::nullptr_t nullp, object_t &c);
    friend bool operator==(object_t &c, std::nullptr_t nullp);
    friend bool operator!=(std::nullptr_t nullp, object_t &c);
    friend bool operator!=(object_t &c, std::nullptr_t nullp);

};

bool
operator==(std::nullptr_t nullp, object_t &o) {
    return o.ptr == nullptr;
}

bool
operator==(object_t &o, std::nullptr_t nullp) {
    return o.ptr == nullptr;
}

bool
operator!=(std::nullptr_t nullp, object_t &o) {
    return o.ptr != nullptr;
}

bool
operator!=(object_t &o, std::nullptr_t nullp) {
    return o.ptr != nullptr;
}

// method_t::invoke implementation
template<typename R, class ...P>
R method_t::invoke(object_t &o, P... params) {
    std::function<R(P...)> (*func)(void*) = (std::function<R(P...)> (*)(void*))this->ptr;
    auto fn = func(o.get_ptr());
    return fn(params...);
}

}

#endif