#ifndef HEADER_gubg_std_cstdint_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_cstdint_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_OS_ARDUINO
namespace std { 
    using uint8_t = ::uint8_t;
} 
#else
#include <cstdint>
#endif

#endif
