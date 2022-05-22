

#pragma once

#include <memory>

namespace hid
{

    namespace internal_ptr_deleter
    {
        template <class T>
        void deleter(T *victim)
        {
            delete victim;
        }
    }


    template <class T, class Deleter = void (*)(T *)>
    using internal_ptr = std::unique_ptr<T, Deleter>;

    template <class T, class... Args>
    inline internal_ptr<T> make_internal_ptr(Args &&...args)
    {
        return internal_ptr<T>(new T(std::forward<Args>(args)...), &internal_ptr_deleter::deleter<T>);
    }
}
