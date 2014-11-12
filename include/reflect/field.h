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

#include <string>
#include "class.h"

namespace rf {

class field_t {

    friend class class_t;

private:

    std::string name;
    void *ptr = nullptr;

    field_t() = delete;
    field_t(std::string name, void *ptr)
    : name(name), ptr(ptr) {}

public:

    template<typename T>
    T &get() {

    }

    friend bool operator==(std::nullptr_t nullp, field_t &c);
    friend bool operator==(field_t &c, std::nullptr_t nullp);
    friend bool operator!=(std::nullptr_t nullp, field_t &c);
    friend bool operator!=(field_t &c, std::nullptr_t nullp);

};


bool
operator==(std::nullptr_t nullp, field_t &c) {
    return c.ptr == nullptr;
}

bool
operator==(field_t &c, std::nullptr_t nullp) {
    return c.ptr == nullptr;
}

bool
operator!=(std::nullptr_t nullp, field_t &c) {
    return c.ptr != nullptr;
}

bool
operator!=(field_t &c, std::nullptr_t nullp) {
    return c.ptr != nullptr;
}

}

#endif