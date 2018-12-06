#ifndef HEADER_gubg_std_array_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_array_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_OS_ARDUINO
namespace std { 

    template <typename T, size_t Size>
    class array
    {
    public:
        size_t size() const {return Size;}

        T &operator[](size_t ix) {return data_[ix];}

        const T *data() const {return data_;}

    private:
        T data_[Size]{};
    };

} 
#else
#include <array>
#endif

#endif
