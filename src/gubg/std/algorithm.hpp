#ifndef HEADER_gubg_std_algorithm_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_algorithm_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_OS_ARDUINO

namespace std { 

#ifdef min
#undef min
#endif
    template <typename T>
    T min(T a, T b) { return a < b ? a : b; }

#ifdef max
#undef max
#endif
    template <typename T>
    T max(T a, T b) { return a > b ? a : b; }

    template <typename It, typename T>
    void fill(It it, It end, const T &value)
    {
        for (; it != end; ++it)
            *it = value;
    }
} 

#else
#include <algorithm>
#endif

#endif
