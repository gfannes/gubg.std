#ifndef HEADER_gubg_std_optional_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_optional_hpp_ALREADY_INCLUDED

#include "gubg/platform/compiler_info.h"

#ifdef GUBG_CC_GCC
#include <optional>
#endif

#ifdef GUBG_CC_MSC
#include <array>
namespace std { 
    template <typename T>
    class optional
    {
    public:
        using Self = optional<T>;

        ~optional() { clear_(); }

        Self &operator=(const T &v) { goc_() = v; return *this; }

    private:
        T &goc_()
        {
            if (!ptr_)
                //Create an empty object, if not present yet
                ptr_ = new (reinterpret_cast<T*>(buffer_.data())) T();
            return *ptr_;
        }
        void clear_()
        {
            if (!ptr_)
                return;
            ptr_->~T();
            ptr_ = nullptr;
        }

        T *ptr_ = nullptr;
        std::array<char, sizeof(T)> buffer_;
    };
} 
#endif

#endif
