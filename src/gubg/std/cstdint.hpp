#ifndef HEADER_gubg_std_cstdint_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_cstdint_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_OS_ARDUINO
namespace std { 
    using uint8_t  = ::uint8_t;
    using uint16_t = ::uint16_t;
    using uint32_t = ::uint32_t;

    using int8_t  = ::int8_t;
    using int16_t = ::int16_t;
    using int32_t = ::int32_t;
} 
#else
#include <cstdint>
#endif

#endif
