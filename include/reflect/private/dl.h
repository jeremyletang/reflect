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

#ifndef REFLECT_DL
#define REFLECT_DL

#include <dlfcn.h>

namespace rf {

namespace priv {

typedef void *(*func_t)();
typedef void *(*meth_t)(void*);
typedef const char *(*meth_to_string_t)();

class dl {

private:

    void *handle = nullptr;

    dl()
    : handle(nullptr) {}

    void* make_handle() {
        // get handle
        void *handle_tmp = dlopen(NULL, RTLD_LAZY);

        // clear error
        dlerror();

        return handle_tmp;
    }

public:

    ~dl() {
        dlclose(this->handle);
    }

    static dl &get_instance() {
            static dl self;
            return self;
    }

    func_t get_constructor(std::string symbol) {
        if (this->handle == nullptr && (this->handle = this->make_handle()) == nullptr) {
            return nullptr;
        }
        void *(*constructor)() = nullptr;
        *(void **) (&constructor) = dlsym(this->handle, symbol.c_str());
        return constructor;
    }

    meth_t get_method(std::string symbol) {
        if (this->handle == nullptr && (this->handle = this->make_handle()) == nullptr) {
            return nullptr;
        }
        void *(*method)(void*) = nullptr;
        *(void **) (&method) = dlsym(this->handle, symbol.c_str());
        return method;
    }

    meth_to_string_t get_method_to_string(std::string symbol) {
        if (this->handle == nullptr && (this->handle = this->make_handle()) == nullptr) {
            return nullptr;
        }
        const char *(*method)() = nullptr;
        *(void **) (&method) = dlsym(this->handle, symbol.c_str());
        return method;
    }

};

}

}

#endif
