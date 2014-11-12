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

// type

#define _rtti_type_1(arg1) \
extern "C" { \
    void *_instanciate_reflectable_type_##arg1() { \
        return new arg1(); \
    } \
}

#define _rtti_type_2(arg1, arg2) \
extern "C" { \
    void *_instanciate_reflectable_type_##arg1##_##arg2() { \
        return new arg1::arg2(); \
    } \
}

#define _rtti_type_3(arg1, arg2, arg3) \
extern "C" { \
    void *_instanciate_reflectable_type_##arg1##_##arg2##_##arg3() { \
        return new arg1::arg2::arg3(); \
    } \
}

#define _rtti_type_4(arg1, arg2, arg3, arg4) \
extern "C" { \
    void *_instanciate_reflectable_type_##arg1##_##arg2##_##arg3##_##arg4() { \
        return new arg1::arg2::arg3::arg4(); \
    } \
}

#define _rtti_type_5(arg1, arg2, arg3, arg4, arg5) \
extern "C" { \
    void *_instanciate_reflectable_type_##arg1##_##arg2##_##arg3##_##arg4##_##arg5() { \
        return new arg1::arg2::arg3::arg4::arg5(); \
    } \
}

#define narg(...) narg_(__VA_ARGS__, rseq_n())
#define narg_(...) arg_n(__VA_ARGS__)
#define arg_n(_1, _2, _3, _4, _5, N, ...) N
#define rseq_n() 5, 4, 3, 2, 1, 0

#define concatenate(arg1, arg2) arg1##arg2

#define _rtti_type(N, ...) concatenate(_rtti_type_, N)(__VA_ARGS__)
#define rtti_type(...) _rtti_type(narg(__VA_ARGS__), __VA_ARGS__)

// method

#define rtti_method(type, method, ret, ...) \
extern "C" { \
    std::function<ret (__VA_ARGS__)> _method_reflectable_##method##_##type(void *instance) { \
        std::function<ret (__VA_ARGS__)> func = std::bind(&type::method, static_cast<type *>(instance)); \
        return func; \
    } \
} \

// field

#define rtti_field(type, field_type, field_name) \
extern "C" { \
    field_type &_field_reflectable_##field_name##_##type(void *instance) { \
        type *real_instance = static_cast<type*>(instance); \
        return real_instance->field_name; \
    } \
} \

#endif