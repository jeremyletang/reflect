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

#ifndef REFLECT_MACROS
#define REFLECT_MACROS

#include <iostream>
#include <functional>

#define rtti_type(type) \
extern "C" { \
    void *_instanciate_reflectable_type_##type() { \
        return new type(); \
    } \
} \

#define rtti_method(type, method, ret, ...) \
extern "C" { \
    std::function<ret (__VA_ARGS__)> _method_reflectable_##method##_##type(void *instance) { \
        std::function<ret (__VA_ARGS__)> func = std::bind(&type::method, static_cast<type *>(instance)); \
        return func; \
    } \
} \

#define rtti_field(type, field_type, field_name) \
extern "C" { \
    field_type &_field_reflectable_##field_name##_##type(void *instance) { \
        type *real_instance = static_cast<type*>(instance); \
        return real_instance->field_name; \
    } \
} \

#endif