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

#ifndef REFLECT_METHOD
#define REFLECT_METHOD

#include <functional>
#include "class.h"
#include "object.h"
#include "private/dl.h"

namespace rf {

#define method_parameters_type_prefix "_method_reflectable_parameters_type_"
#define method_return_type_prefix "_method_reflectable_return_type_"

class method_t {

    friend class class_t;

private:

    std::string name_;
    std::string type_name;
    void *(*ptr)(void*) = nullptr;

    std::string to_string_ = "";
    std::string return_type_ = "";
    std::string parameters_type_ = "";

    method_t() = delete;
    method_t(std::string name, std::string type_name, void *(*ptr)(void*))
    : name_(name), type_name(type_name), ptr(ptr) {}

public:

    template<typename R = void, class ...P>
    R invoke(object_t &o, P... params) {
        std::function<R(P...)> (*func)(void*) = (std::function<R(P...)> (*)(void*))this->ptr;
        auto fn = func(o.get_ptr());
        return fn(params...);
    }

    std::string &name() {
        return this->name_;
    }

    std::string &to_string() {
        if (this->to_string_ == "") {
            this->to_string_ += this->return_type();
            this->to_string_ += " ";
            this->to_string_ += this->name_;
            this->to_string_ += "(";
            this->to_string_ += this->parameters_type();
            this->to_string_ += ")";
        }

        return this->to_string_;
    }

    std::string &return_type() {
        if (this->return_type_ == "") {
            const char *(*ptr_method)();
            std::string fn_name = method_return_type_prefix;
            fn_name += this->name_;
            fn_name += "_";
            fn_name += this->type_name;
            ptr_method = dl::get_instance().get_method_to_string(fn_name);
            this->return_type_ = ptr_method();
        }

        return this->return_type_;
    }

    std::string &parameters_type() {
        if (this->parameters_type_ == "") {
            const char *(*ptr_method)();
            std::string fn_name = method_parameters_type_prefix;
            fn_name += this->name_;
            fn_name += "_";
            fn_name += this->type_name;
            ptr_method = dl::get_instance().get_method_to_string(fn_name);
            this->parameters_type_ = ptr_method();
        }

        return this->parameters_type_;
    }

    friend bool operator==(std::nullptr_t nullp, method_t &c);
    friend bool operator==(method_t &c, std::nullptr_t nullp);
    friend bool operator!=(std::nullptr_t nullp, method_t &c);
    friend bool operator!=(method_t &c, std::nullptr_t nullp);

};

bool
operator==(std::nullptr_t nullp, method_t &c) {
    return c.ptr == nullptr;
}

bool
operator==(method_t &c, std::nullptr_t nullp) {
    return c.ptr == nullptr;
}

bool
operator!=(std::nullptr_t nullp, method_t &c) {
    return c.ptr != nullptr;
}

bool
operator!=(method_t &c, std::nullptr_t nullp) {
    return c.ptr != nullptr;
}

}

#endif