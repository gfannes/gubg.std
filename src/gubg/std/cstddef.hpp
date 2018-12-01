#ifndef HEADER_gubg_std_cstddef_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_cstddef_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_COMPILER_GCC
#if GUBG_PLATFORM_OS_ARDUINO
namespace std { 
    enum class byte: unsigned char {};
} 
#else
#include <cstddef>
#endif
#endif

#if GUBG_PLATFORM_COMPILER_MSVC
#include <cstddef>
namespace std { 
    enum class byte: unsigned char {};
} 
#endif

#endif
